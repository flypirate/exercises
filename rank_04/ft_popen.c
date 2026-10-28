#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int ft_popen(const char *file, char *const argv[], char type)
{
	int	fd[2];
	pid_t forkresult;

	if (!file || !argv)
		return (-1);
	if (!argv[0] || (type != 'r' && type != 'w'))
		return (-1);

	if (pipe(fd) == -1)
		return (-1);
	forkresult = fork();
	if (forkresult < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (forkresult == 0)
	{
		if (type == 'r')
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			execvp(file, argv);
			exit(1);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			execvp(file, argv);
			exit(1);
		}		
	}
	if (type == 'r')
		return (close(fd[1]), fd[0]);
	else
		return (close(fd[0]), fd[1]);
}


int	main() {
	int fd;
	char buf[5];
	size_t count = 5;
	int	bytes;

	fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
	while (bytes = read(fd, buf, count), bytes > 0)
	{
		//printf("bytes read = %d\n", bytes);
        write(fd, buf, 5);
	}	
	close(fd);
    return (0);
}
fd[1] → extremo de escritura

*/

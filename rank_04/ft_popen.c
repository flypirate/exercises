/* Assignment name  : ft_popen
Expected files   : ft_popen.c
Allowed functions: pipe, fork, dup2, execvp, close, exit
--------------------------------------------------------------------------------------

Write the following function:

int ft_popen(const char *file, char *const argv[], char type);

The function must launch the executable file with the arguments argv (using execvp).
If type is 'r' the function must return a file descriptor connected to the output of the command.
If type is 'w' the function must return a file descriptor connected to the input of the command.
In case of error or invalid parameter the function must return -1.

For example, the function could be used like that:

int main()
{
    int  fd;
    char *line;

    fd = ft_popen("ls", (char *const []){"ls", NULL}, 'r');
    while ((line = get_next_line(fd)))
        ft_putstr(line);
    return (0);
}
*/

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


/*
Hints:
Do not leak file descriptors!
This exercise is inspired by the libc's popen().

fd[0] → extremo de lectura
fd[1] → extremo de escritura

*/
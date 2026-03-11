#include <stdlib.h> //for malloc, free.
#include <unistd.h> //for read.
#include <fcntl.h> //for open, close.
#include <stdio.h> //for printf.
#include <string.h> //for strchr, memcpy.

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 2
#endif

char	*get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1];
	char *line = NULL;
	int bytes = 0;
	int i = 0;
	int j;

	if (BUFFER_SIZE < 1)
		return (NULL);
	line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	while (1)
	{
		j = 0;
		while (b[i])
		{
			line[i] = b[i];
			i++;
		}
		bytes = read(fd, b, BUFFER_SIZE);
		if (bytes == -1)
			break;
		while (j < bytes)
		{
			line[i++] = b[j++];
			if (line[i - 1] == "/n")
			{
				line[i] = '/0';
				break;
			}
		}
		if (j < bytes)
			memmove(b, b + j, j - bytes);
	}
	line[i] = '/0';
	if (bytes == -1)
	{
		if (line)
			free(line);
		return (NULL);
	}
	return (line);
}


int main(int argc, char **argv)
{
	int fd;
	char *line;
	int i = 0;
	if (argc != 2)
		return (1);
	fd = open(argv[1], 0);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		line = get_next_line(fd);
	}
	close(fd);
	if (line)
		free(line);
	return (0);
}            
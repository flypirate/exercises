#include <stdlib.h> //for malloc, free.
#include <unistd.h> //for read.
#include <fcntl.h> //for open, close.
#include <stdio.h> //for printf.
#include <string.h> //for strchr, memcpy.

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

char	*get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1];
	char *line;
	char *temp = NULL;
	int bytes = 0;
	int i = 0;
	int j;

	if (BUFFER_SIZE < 1)
		return (NULL);
	line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	line[i] = '\0';
	while (1)
	{
		temp = realloc(line, sizeof(char) * (strlen(line) + BUFFER_SIZE + 1));
		if (!temp)
			return (free(line), NULL);
		line = temp;
		j = 0;
		if (b[0])
			memmove(line, b, strlen(b) + 1);
		i = strlen(line);
		bytes = read(fd, b, BUFFER_SIZE);
		if (bytes < 1)
			break;
		b[bytes] = '\0';
		while (j < bytes)
		{
			line[i++] = b[j++];
			if (line[i - 1] == '\n')
			{
				line[i] = '\0';
				break;
			}
		}
		if (j < bytes)
			memmove(b, b + j, strlen(b + j) + 1);
		else
			b[0] = '\0';
		break;
	}
	line[i] = '\0';
	if (bytes == 0 && b[0])
	{
		b[0] = '\0';
		return (line);
	}
	if (bytes == -1 || bytes == 0 && !b[0])
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
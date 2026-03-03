#include <stdlib.h> //for malloc, free.
#include <unistd.h> //for read.
#include <fcntl.h> //for open, close.
#include <stdio.h> //for printf.
#include <string.h> //for strchr, memcpy.

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 2
#endif

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1];
	static char *stash;
	char *line = NULL;
	char *nl = NULL;
	int bytes = 0;
	int i = 0;
	int j;
	int k = 0;

	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	line[0] = '\0';
	if (!stash)
	{
		stash = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	while (1)
	{
		j = 0;
		if (stash[0])
		{
			memmove(line, stash, strlen(stash));
			stash[0] = '\0';
			i = strlen(line);
		}
		bytes = read(fd, b, BUFFER_SIZE);
		if (bytes < 1)
			break;
		b[bytes] = '\0';
		while (j < bytes)
		{
			line = realloc(line, sizeof(char) * (BUFFER_SIZE + 1 + strlen(line)));
			if (!line)
				return (free(stash), NULL);
			line[i++] = b[j++];
			if (line[i - 1] == '\n')
				break;
		}
		break;
	}
	line[i] = '\0';
	if (nl = strchr(line, '\n'), nl)
	{
		while (j < bytes)
			stash[k++] = b[j++];
		stash[k] = '\0';
		nl++;
		*nl = '\0';
	}
	else if (bytes == -1)
	{
		if (line)
			free(line);
		return (NULL);
	}
	else if (bytes == 0 && stash[0])
	{
		memmove(line, stash, strlen(stash));
		line[strlen(stash)] = '\0';
		free(stash);
		stash = NULL;
	}
	else if (bytes == 0 && !stash[0])
		return NULL;
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
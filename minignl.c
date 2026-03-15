#include <stdlib.h> //for malloc, free.
#include <unistd.h> //for read.
#include <fcntl.h> //for open, close.
#include <stdio.h> //for printf.
#include <string.h> //for strchr, memcpy.

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char *ft_strdup(char *string, int c)
{
	int i = 0;
	char *ret;
	if (!string)
		return NULL;
	ret = malloc(sizeof(char) * (c + 1));
	if (!ret)
		return NULL;
	while (i < c)
	{
		ret[i] = string[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);		
}

char *get_next_line(int fd)
{
	static char buf[BUFFER_SIZE + 1];
	static char line[7000];
	char *ret = NULL;
	static int bytes;
	static int i;
	static int j;

	while (1)
	{
		if (j >= bytes)
		{
			j = 0;
			bytes = read(fd, buf, BUFFER_SIZE);
			buf[bytes] = '\0';
			if (bytes < 1)
				break;
		}
		line[i++] = buf[j++];
		if (line[i - 1] == '\n')
			break;
	}
	if (bytes == -1)
		return (NULL);
	if (bytes == 0 && i == 0)
		return (NULL);
	if (i > 0)
	{
		ret = ft_strdup(line, i);
		i = 0;
		return (ret);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	int fd;
	char *line;
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
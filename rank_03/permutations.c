#include <stdlib.h>
#include <stdio.h>

void swap(char *a, char *b)
{
	char temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void sort_1(char *str, int index)
{
	int i = index;
	int j;

	while(str[i])
	{
		j = i + 1;
		while(str[j])
		{
			if(str[i] > str[j])
				swap(&str[i], &str[j]);
			j++;	
		}
		i++;
	}
}

void permutations(char *arg, int len, int index)
{
	int i = index;
	//printf("aqui\n");
	if (index == len)
	{
		puts(arg);
		return;
	}
	while (i < len)
	{
		swap(&arg[index], &arg[i]);
		//sort_1(arg, index);
		permutations(arg, len, index + 1);
		swap(&arg[index], &arg[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int len = 0;
	
	while (argv[1][len])
		len++;
	sort_1(argv[1], 0);
	permutations(argv[1], len, 0);
	return (0);
}
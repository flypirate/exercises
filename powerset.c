/*Allowed functions : atoi, printf, malloc, calloc, realloc, free.
---------------------------------------------------------------

Write a program that will take as argument an integer n follow by a set of integers,
your program should display all the subsets of whose sum of elements is n.

In case of a malloc error your program will exit with the code 1.
We will not test invalid test(for example '1 1 2')
hint: the empty set is a subset of anyset.*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void powerset(int n, int len, int *subset, int *buf, int sum, int buflen, int sublen)
{
	if (sublen > len)
		return;
	if (sum == n)
	{
		int k = 0;
		//printf("buflen = %d\n", buflen);
		while (k < buflen)
		{
			printf("%d", buf[k]);
			if (k < buflen - 1)
				printf(" ");
			k++;
		}
		printf("\n");
		return;
	}
	sum += subset[sublen];
	if (sum > n)
	{
		powerset(n, len, subset, buf, sum, buflen, sublen + 1);
		return ;
	}
	buf[buflen++] = subset[sublen++];
	powerset(n, len, subset, buf, sum, buflen, sublen);
	sublen--;
	buflen--;
	sum -= subset[sublen];
	powerset(n, len, subset, buf, sum, buflen, sublen + 1);
}


int main(int argc, char **argv)
{
	if (argc < 3)
		return (1);
	int len = argc - 2;
	int subset[len];
	int *buf;
	int i = 2;
	int j = 0;
	int n = atoi(argv[1]);
	if (n < 0)
		return (1);
	while (argv[i])
	{
		subset[j] = atoi(argv[i]);
		i++;
		j++;
	}
	i = 0;
	buf = malloc(sizeof(int) * len);
	if (!buf)
		return (1);
	powerset(n, len, subset, buf, 0, 0, 0);
	return (0);
}
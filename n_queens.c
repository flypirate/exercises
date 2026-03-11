#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int check_valid(int *tablero, int size, int col)
{
	int i = 0;
	int diag;
	while (i < col)
	{
		if (tablero[col] == tablero[i])
			return (0);
		diag = tablero[col] - tablero[i];
		if (diag < 0)
			diag = diag * -1;
		if (diag == col - i)
			return (0);
		i++;
	}
	return (1);
}	

void nqueens(int *tablero, int size, int col, int fil)
{
	if (fil == size)
		return ;
	if (col == size)
	{
		int i = 0;
		while (i < size)
		{
			printf("%d", tablero[i]);
			if (i < size - 1)
				printf(" ");
			i++;
		}
		printf("\n");
		return ;
	}	
	if (check_valid(tablero, size, col))
	{
		tablero[col] = fil;
		nqueens(tablero, size, col + 1, 0);
	}
	nqueens(tablero, size, col, fil + 1);
	printf("Aqui");
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int size = atoi(argv[1]);
	if (size < 2)
		return(1);
	int tablero[size];
	int i = 0;
	while (i < size)
		tablero[i++] = 0;
	int col = 0;
	int fil = 0;
	nqueens(tablero, size, col, fil);
	return (0);
}

/*
Assignment name: rip
Expected files: *.c *.h
Allowed functions: puts, write
--------------------------------------------------------------------------------
Write a program that will take as argument a string containing only parenthesis.
If parenthesis are unbalanced (for example "())") your program shall remove the
minimum number of parenthesis for the expression to be balanced.
By removing we mean replacing by spaces.
You will print all the solutions (can be more than one).
The order of the solutions is not important.
For example this should work:
(For readability reasons the '_' means space and the spaces are for readability only.)
$> ./rip '( ( )' | cat -e
_ ( ) $
( _ ) $
$> ./rip '( ( ( ) ( ) ( ) ) ( ) )' | cat -e
( ( ( ) ( ) ( ) ) ( ) ) $
$> ./rip '( ) ( ) ) ( )' | cat -e
( ) ( ) _ ( ) $
( ) ( _ ) ( ) $
( _ ( ) ) ( ) $
$> ./rip '( ( ) ( ( ) (' | cat -e
( ( ) _ _ ) _ $
( _ ) ( _ ) _ $
( _ ) _ ( ) _ $
_ ( ) ( _ ) _ $
_ ( ) _ ( ) _ $
*/
#include <stdio.h>
#include <unistd.h>

//opened: abiertos acumulados

int	min_to_del(char *arg, int len)
{
	int i = 0;
	int closed = 0;
	int opened = 0;
	while (i < len)
	{
		if (arg[i] == '(')
			opened++;
		else if (arg[i] == ')')
		{
			if (opened > 0)
				opened--;
			else
				closed++;
		}		
		i++;
	}
	return (opened + closed);
}

void	rip(char *arg, int len, int pos, int mintodel, int removed, int opened)
{
	char temp = 0;
	if (pos == len)
	{
		if (removed == mintodel && opened == 0)
			puts(arg);
		return ;
	}
	if (removed > mintodel)
		return;
	if (arg[pos] == '(' || arg[pos] == ')')
	{
		temp = arg[pos];
		arg[pos] = ' ';
		rip(arg, len, pos + 1, mintodel, removed + 1, opened);
		arg[pos] = temp;
	}
	if (arg[pos] == '(')
		rip(arg, len, pos + 1, mintodel, removed, opened + 1);
	else if (arg[pos] == ')' && opened > 0)
		rip(arg, len, pos + 1, mintodel, removed, opened - 1);
}

int main(int argc, char **argv)
{
	int len = 0;
	int open = 0;
	int init = 0;
	if (argc != 2)
		return (1);
	while (argv[1][len])
		len++;
	int mintodel = min_to_del(argv[1], len);
	if (mintodel == 0)
		return (0);
	//printf("toremove = %d\n", toremove);
	rip(argv[1], len, 0, mintodel, 0, 0);
	return (0);
}

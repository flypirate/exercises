#include <stdio.h>
#include <unistd.h>

int	calc_diff(char *arg, int len)
{
	int i = 0;
	int toremove = 0;
	while (i < len)
	{
		if (arg[i] == '(')
			toremove++;
		else if (arg[i] == ')')
			toremove--;
		i++;
	}
	return (toremove);
}

void	rip(char *arg, int len, int diff, int pos, int toremove)
{
	if (pos == len)
	{
		if (diff == 0)
			puts(arg);
		return ;
	}
	if (arg[pos] == ')')
	{
		rip(arg, len, diff - 1, pos + 1, toremove);
		if (diff == 0 && toremove != 0)
		{
			arg[pos] = '_';
			rip(arg, len, diff, pos + 1, toremove - 1);
			arg[pos] = ')';
		}
	}
	else if (arg[pos] == '(')
	{
		rip(arg, len, diff + 1, pos + 1, toremove);
		if (toremove > 0)
		{
			arg[pos] = '_';
			rip(arg, len, diff, pos + 1, toremove - 1);
			arg[pos] = '(';
		}
	}
	return;
}

int main(int argc, char **argv)
{
	int len = 0;
	int open = 0;
	int closed = 0;
	int init = 0;
	if (argc != 2)
		return (1);
	while (argv[1][len])
		len++;
	int toremove = calc_diff(argv[1], len);
	rip(argv[1], len, 0, 0, toremove);
	return (0);
}

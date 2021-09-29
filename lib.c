#include "minitalk.h"

void do_exit(void)
{
fprintf(stderr, "egzitink\n");
	exit(0);
}

unsigned int ft_atoi(char *str)
{
	unsigned long int rst;

	rst = 0;
	while (*str >= '0' && *str <= '9' && rst < UINT_MAX)
	{
		rst = rst * 10;
		rst = rst + *str - '0';
		str++;
	}
	if(rst <= UINT_MAX)
		return ((unsigned int)rst);
	else
		do_exit();
}
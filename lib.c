#include "minitalk.h"

void do_exit(void)
{
	exit(0);
}

unsigned int ft_atoi(char *str)
{
//fprintf(stderr, "ft_atoi start. str = %s\n", str);
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

static void ft_write_pid_rec(pid_t nbr)
{
	int i;
	char c;

	i = 0;

	if (nbr / 10)
	{
		ft_write_pid_rec(nbr/10);

		c = (char)(nbr % 10) + '0';
		write(1, &c, 1);
	}
	else if (nbr % 10)
	{
		c = ((char)(nbr) % 10) + '0';
		write(1, &c, 1);
	}
}

void ft_write_pid(pid_t nbr)
{
	if (nbr)
		ft_write_pid_rec(nbr);
	else
		write(1, "0", 1);
}

// void ft_signal(unsigned int msg, int mode)
// {
// 	static pid_t pid;

// 	if (mode == 0)
// 		pid = msg;
// 	else
// 	{
// 		if (msg == 0)
// 			kill(pid, SIGUSR1);
// 		else
// 			kill(pid, SIGUSR2);
// 	}

// }
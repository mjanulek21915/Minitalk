#include "minitalk.h"

void ft_pass(int sig, siginfo_t *info, void *context)
{

}

static void ft_client_transmit_byte(pid_t pid, char c)
{
	int i;
	unsigned char rst;

	rst = 0;
	i = 0;
	while (i < 8)
	{
		rst = c & 128;
		c = c << 1;
		if (rst == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(10000);

		i++;
	}
}

static void ft_client_transmit(pid_t pid, char *str)
{
	while (*str)
	{
		ft_client_transmit_byte(pid, *str);
		str++;
	}
}

int main(int ac, char **av)
{
	pid_t pid;
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if ((sigaddset(&sa.sa_mask, SIGUSR1)) || (sigaddset(&sa.sa_mask, SIGUSR2)))
	{
		return(0);
	}
	sa.sa_sigaction = ft_pass;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	if (ac != 3)
		return (0);
	if (!(pid = ft_atoi(av[1])))
	{
	
		return(0);
	}
	ft_client_transmit(pid, av[2]);
}
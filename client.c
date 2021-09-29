#include "minitalk.h"

void	ft_connect_confirm(int sig, siginfo_t *info, void *context)
{
	if (info->si_pid == client_args.id)
		client_args.success = 1;
}

void				ft_transmit_char(unsigned char c)
{
	int i;
	unsigned char rst;

	rst = 0;
	i = 0;
	while (i < 8)
	{
		rst = c & 128;
		c = c << 1;
		usleep(MINITALK_MOMENT * 10);
		if (rst == 0)
		{
			kill(client_args.id, SIGUSR1);

		}
		else
		{

			kill(client_args.id, SIGUSR2);
		}
		i++;
	}
	client_args.success = 0;
	while (client_args.success == 0)
		pause();
}

void				ft_connect(void)
{

	client_args.sa->sa_sigaction = ft_connect_confirm;
	sigaction(SIGUSR1, client_args.sa, NULL);
	sigaction(SIGUSR2, client_args.sa, NULL);

	while (client_args.success == 0)
	{
		kill(client_args.id, SIGUSR1);
		usleep(50000);
	}
}


void				ft_transmit(char *str)
{
	while (*str)
	{
		kill(client_args.id, SIGUSR1);
		usleep(MINITALK_MOMENT * 3);
		ft_transmit_char(*str);
		str++;
	}
fprintf(stderr, "transmit ok");
	kill(client_args.id, SIGUSR2);
}


int main(int ac, char **av)
{
	t_sigaction sa;

	if (ac != 3)
	{
		return (0);
	}
// fprintf(stderr, "str : %s", av[2]);
	client_args.success = 0;
	client_args.id = ft_atoi(av[1]);
	client_args.sa = &sa;
	client_args.rst = 0;
	client_args.pos = 0;
	sa.sa_flags = SA_SIGINFO;
	ft_connect();
	ft_transmit(av[2]);
}
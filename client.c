/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjanulek <mjanulek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:11:04 by mjanulek          #+#    #+#             */
/*   Updated: 2021/10/18 15:11:04 by mjanulek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_pass(int sig, siginfo_t *info, void *context)
{
}

static void	ft_client_transmit_byte(pid_t pid, char c)
{
	int				i;
	unsigned char	rst;

	rst = 0;
	i = 0;
	while (i < 8)
	{
		rst = c & 128;
		c = c << 1;
		if (rst == 0)
			ft_send_signal(pid, SIGUSR1);
		else
			ft_send_signal(pid, SIGUSR2);
		usleep(10000);
		i++;
	}
}

static void	ft_client_transmit(pid_t pid, char *str)
{
	while (*str)
	{
		ft_client_transmit_byte(pid, *str);
		str++;
	}
}

int	main(int ac, char **av)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if ((sigemptyset(&sa.sa_mask)) || (sigaddset(&sa.sa_mask, SIGUSR1))
		|| (sigaddset(&sa.sa_mask, SIGUSR2)))
		return (0);
	sa.sa_sigaction = ft_pass;
	if ((sigaction(SIGUSR1, &sa, NULL)) || (sigaction(SIGUSR2, &sa, NULL)))
		return (0);
	if (ac != 3)
		return (0);
	pid = ft_atoi(av[1]);
	ft_client_transmit(pid, av[2]);
}

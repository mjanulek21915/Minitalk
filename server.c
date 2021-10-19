/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjanulek <mjanulek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:11:04 by mjanulek          #+#    #+#             */
/*   Updated: 2021/10/18 15:11:04 by mjanulek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_listen(int sig, siginfo_t *info, void *context)
{
	static int	pos = 0;
	static char	rst = 0;

	if (sig == SIGUSR1)
	{
		rst = rst << 1;
		rst = rst + 0;
	}
	else if (sig == SIGUSR2)
	{
		rst = rst << 1;
		rst = rst + 1;
	}
	pos++;
	if (pos == 8)
	{
		write(1, &rst, 1);
		pos = 0;
		rst = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(int ac, char **av)
{
	struct	sigaction sa;
	pid_t	pid;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_listen;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_write_pid(getpid());
	while (1)
		pause();
}

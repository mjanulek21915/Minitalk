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

void ft_listen(int sig, siginfo_t *info, void *context)
{
//fprintf(stderr, "ft_listen pid = %d\n", info->si_pid);
	static int pos = 0;
	static char rst = 0;

	if (sig == SIGUSR1)
	{
//fprintf(stderr, "sending 0\n");
		rst = rst << 1;
		rst = rst + 0;
	}
	else if (sig == SIGUSR2)
	{
//fprintf(stderr, "sending 1\n");
		rst = rst << 1;
		rst = rst + 1;
	}
	pos++;
//fprintf(stderr, "ft_listen pos = %d\n", pos);
// //fprintf(stderr, "ft_listen pos true : %d\n", (pos == 8));
	if (pos == 8)
	{
// //fprintf(stderr, ">>>ft_listen pos == 8\n");
//fprintf(stderr, ">%hhu<\n", rst);
//fprintf(stderr, ">");
		write(1, &rst, 1);
//fprintf(stderr, ">\n");
		pos = 0;
		rst = 0;
	}
//fprintf(stderr, ">confirm next\n");
// usleep(100);
	kill(info->si_pid, SIGUSR1);
}

int main(int ac, char **av)
{
	struct sigaction sa;
	pid_t pid;
//fprintf(stderr, "size of pid = %ld\n", sizeof(pid_t));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_listen;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_write_pid(getpid());
//fprintf(stderr, "\n");
	while (1)
		pause();
}
#include "minitalk.h"


void	ft_on_confirmation_server(int sig, siginfo_t *info, void *context);

void	ft_on_connect_server(int sig, siginfo_t *info, void *context)
{
	if (server_args.success == 0)
	{
		server_args.id = info->si_pid;

		server_args.sa->sa_sigaction = ft_on_confirmation_server;
		sigaction(SIGUSR1, server_args.sa, NULL);
		sigaction(SIGUSR2, server_args.sa, NULL);
		usleep(MINITALK_MOMENT);
		kill(server_args.id, SIGUSR1);
		server_args.success = 1;
	}

}

void	ft_on_reception_server(int sig, siginfo_t *info, void *context)
{
	if (info->si_pid == server_args.id)
	{
		server_args.pos = server_args.pos + 1;
		if (sig == SIGUSR1)
		{
			server_args.rst = server_args.rst << 1;
			server_args.rst = server_args.rst + 0;
		}
		else if (sig == SIGUSR2)
		{
			server_args.rst = server_args.rst << 1;
			server_args.rst = server_args.rst + 1;
		}
		if (server_args.pos == 8)
		{
			write(1, &(server_args.rst), 1);
			server_args.pos = 0;
			server_args.rst = 0;
			server_args.sa->sa_sigaction = ft_on_confirmation_server;
			sigaction(SIGUSR1, server_args.sa, NULL);
			sigaction(SIGUSR2, server_args.sa, NULL);
			usleep(MINITALK_MOMENT);
			kill(server_args.id, SIGUSR1);
		}
	}
}

void	ft_on_confirmation_server(int sig, siginfo_t *info, void *context)
{
	if (info->si_pid == server_args.id)
	{
		if (sig == SIGUSR1)
		{
			server_args.sa->sa_sigaction = ft_on_reception_server;
			sigaction(SIGUSR1, server_args.sa, NULL);
			sigaction(SIGUSR2, server_args.sa, NULL);
			usleep(MINITALK_MOMENT);
			kill(server_args.id, SIGUSR1);
		}
		else if (sig == SIGUSR2)
		{
			server_args.success = 0;
			server_args.sa->sa_sigaction = ft_on_connect_server;
			sigaction(SIGUSR1, server_args.sa, NULL);
			sigaction(SIGUSR2, server_args.sa, NULL);
		}
	}
}

int main()
{
	t_sigaction sa;

	server_args.success = 0;
	server_args.id = 0;
	server_args.sa = &sa;
	server_args.rst = 0;
	server_args.pos = 0;
	printf("PID: %d\n", getpid());	   //display PID for kill()
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = ft_on_connect_server;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
}
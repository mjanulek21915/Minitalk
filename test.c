#include <signal.h>
#include <unistd.h>
#include <stdio.h>


static volatile int signalPid = -1;
void	get_pid(int sig, siginfo_t *info, void *context)
{
	signalPid = info->si_pid;
}

int main(int argc, char **argv)
{
	t_sigaction		sa;

	printf("PID: %d\n", getpid());	   //display PID for kill()
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = get_pid;
	sigaction(SIGUSR1, &sa, NULL);
	pause();						   //wait for a signal
	printf("PID of signal sender = %d\n", signalPid);
}
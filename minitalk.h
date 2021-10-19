#ifndef __MINITALK_H__
#define __MINITALK_H__

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

void ft_listen(int sig, siginfo_t *info, void *context);
void ft_write_pid(pid_t nbr);
unsigned int ft_atoi(char *str);
void do_exit(void);

#endif
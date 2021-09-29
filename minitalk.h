#ifndef __MINITALK_H__
#define __MINITALK_H__

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

unsigned int ft_atoi(char *str);
void do_exit(void);

struct												s_server_args;
typedef struct s_server_args						t_server_args;

struct												sigaction;
typedef struct sigaction							t_sigaction;

struct												s_server_args
{
	pid_t id;
	int success;
	t_sigaction *sa;
	int pos;
	unsigned char rst;
};

t_server_args server_args;
t_server_args client_args;

#define MINITALK_MOMENT 30


#endif
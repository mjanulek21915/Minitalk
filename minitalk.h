/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjanulek <mjanulek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:11:04 by mjanulek          #+#    #+#             */
/*   Updated: 2021/10/18 15:11:04 by mjanulek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MINITALK_H__
#define __MINITALK_H__

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
void				do_exit(void)
void				ft_listen(int sig, siginfo_t *info, void *context);
void				ft_write_pid(pid_t nbr);
unsigned int		ft_atoi(char *str);
void				do_exit(void)

#endif
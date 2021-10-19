/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjanulek <mjanulek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:11:04 by mjanulek          #+#    #+#             */
/*   Updated: 2021/10/18 15:11:04 by mjanulek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	do_exit(void)
{
	exit(0);
}

unsigned int	ft_atoi(char *str)
{
	unsigned long int	rst;

	rst = 0;
	while (*str >= '0' && *str <= '9' && rst < UINT_MAX)
	{
		rst = rst * 10;
		rst = rst + *str - '0';
		str++;
	}
	if (rst <= UINT_MAX)
		return ((unsigned int)rst);
	else
		do_exit();
}

static void	ft_write_pid_rec(pid_t nbr)
{
	int i;
	char c;

	i = 0;

	if (nbr / 10)
	{
		ft_write_pid_rec(nbr/10);

		c = (char)(nbr % 10) + '0';
		write(1, &c, 1);
	}
	else if (nbr % 10)
	{
		c = ((char)(nbr) % 10) + '0';
		write(1, &c, 1);
	}
}

void				ft_write_pid(pid_t nbr)
{
	if (nbr)
		ft_write_pid_rec(nbr);
	else
		write(1, "0", 1);
}
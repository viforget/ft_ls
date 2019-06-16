/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 00:02:35 by viforget          #+#    #+#             */
/*   Updated: 2018/10/20 01:36:38 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	long	a;
	long	nb;
	char	neg;

	a = 0;
	nb = 0;
	neg = 0;
	while ((str[a] == ' ') || (str[a] == '\t') || (str[a] == '\v')
			|| (str[a] == '\n') || (str[a] == '\r') || (str[a] == '\f'))
		a++;
	if (str[a] == '-')
		neg = 1;
	if (str[a] == '-' || str[a] == '+')
		a++;
	while ((str[a] >= '0') && (str[a] <= '9'))
	{
		nb *= 10;
		nb += ((long)str[a] - '0');
		a++;
	}
	if (neg == 1)
		return (-nb);
	else
		return (nb);
}

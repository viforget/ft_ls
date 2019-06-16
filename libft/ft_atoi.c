/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viforget <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 12:11:43 by viforget          #+#    #+#             */
/*   Updated: 2018/10/20 00:09:05 by viforget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int		a;
	int		nb;
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
		nb += ((int)str[a] - '0');
		a++;
	}
	if (neg == 1)
		return (-nb);
	else
		return (nb);
}

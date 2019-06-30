/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmultstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 23:25:47 by ntom              #+#    #+#             */
/*   Updated: 2019/06/30 18:00:24 by ntom             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

int			put_mult_str(int num, ...)
{
	va_list		ap;
	char		*tmp;

	va_start(ap, num);
	tmp = NULL;
	while (num != 0)
	{
		tmp = va_arg(ap, char *);
		ft_putstr(tmp);
		num--;
	}
	va_end(ap);
	return (0);
}

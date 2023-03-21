/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:13:37 by tguerin           #+#    #+#             */
/*   Updated: 2022/10/07 00:13:17 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	get_len(long value)
{
	int	len;

	len = 1;
	while (value / 10 > 0)
	{
		len++;
		value /= 10;
	}
	return (len);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	value;
	int		len;
	int		tmp;

	value = n;
	if (n < 0)
		value *= -1;
	len = get_len(value);
	if (n < 0)
		ft_putchar_fd('-', fd);
	while (len)
	{
		tmp = value / (int)pow(10.0, (double)len - 1.0);
		ft_putchar_fd(tmp + '0', fd);
		value -= (int)pow(10.0, (double)len - 1.0) * tmp;
		len--;
	}
}

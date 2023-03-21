/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:35:09 by tguerin           #+#    #+#             */
/*   Updated: 2022/12/09 22:05:20 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	get_sign(const char *nptr, int begin)
{
	if (nptr[begin] == '-')
		return (-1);
	return (1);
}

static int	first_non_white_space(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	return (i);
}

static int	is_overflow(long result, long old_result, int sign)
{
	if (sign == -1 && result == LONG_MIN)
		return (0);
	return (result / 10 != old_result);
}

long	ft_atol(const char *nptr, int *error_flag)
{
	long	result;
	long	old_result;
	int		sign;
	int		i;

	i = first_non_white_space(nptr);
	sign = get_sign(nptr, i);
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	result = 0;
	old_result = 0;
	while (ft_isdigit(nptr[i]))
	{
		result *= 10;
		result += nptr[i] - '0';
		if (is_overflow(result, old_result, sign))
		{
			*error_flag = 1;
			return (-1 + (sign == -1));
		}
		old_result = result;
		i++;
	}
	return (result * sign);
}

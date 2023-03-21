/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:25:46 by tguerin           #+#    #+#             */
/*   Updated: 2022/12/09 22:48:05 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_split_len(char **split)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (split[i])
	{
		len += ft_strlen(split[i]);
		i++;
	}
	return (len);
}

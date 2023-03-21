/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:50:39 by tguerin           #+#    #+#             */
/*   Updated: 2023/02/02 23:59:14 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_split_print(char **split)
{
	int		i;

	if (!split)
		ft_putstr_fd("(null)\n", 1);
	if (!split[0])
		ft_putstr_fd("[]\n", 1);
	ft_putstr_fd("[ '", 1);
	i = 0;
	while (split[i])
	{
		ft_putstr_fd(split[i], 1);
		if (split[i + 1])
			ft_putstr_fd("', '", 1);
		i++;
	}
	ft_putstr_fd(" ']\n", 1);
}

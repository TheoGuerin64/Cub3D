/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:25:05 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/10 15:31:22 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_split_count(char **split, const char *s)
{
	int	count;
	int	len;
	int	i;

	len = ft_strlen(s);
	count = 0;
	i = 0;
	while (split[i])
	{
		if (ft_strncmp(split[i], s, len + 1) == 0)
			count++;
		i++;
	}
	return (count);
}

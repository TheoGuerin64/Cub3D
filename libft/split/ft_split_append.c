/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:12:36 by tguerin           #+#    #+#             */
/*   Updated: 2022/12/10 00:12:42 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_split_append(char ***split, const char *value)
{
	char	**new_split;
	int		i;

	new_split = malloc(sizeof(*new_split) * (ft_split_size(*split) + 2));
	if (!new_split)
		return (0);
	i = 0;
	while ((*split)[i])
	{
		new_split[i] = (*split)[i];
		i++;
	}
	new_split[i] = ft_strdup(value);
	new_split[i + 1] = NULL;
	free(*split);
	*split = new_split;
	return (1);
}

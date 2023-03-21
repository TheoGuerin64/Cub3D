/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:46:16 by tguerin           #+#    #+#             */
/*   Updated: 2022/12/12 15:01:36 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	dup_except(char **split, char **new_split, int index)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (split[i])
	{
		if (i != index)
		{
			new_split[j] = split[i];
			j++;
		}
		else
			free(split[i]);
		i++;
	}
	new_split[j] = NULL;
}

int	ft_split_remove(char ***split, int index)
{
	char	**new_split;

	if (index >= ft_split_size(*split))
	{
		ft_fprintf(2, "ft_split_remove: %d: index out of range", index);
		return (0);
	}
	new_split = malloc(sizeof(*new_split) * ft_split_size(*split));
	if (!new_split)
		return (0);
	dup_except(*split, new_split, index);
	free(*split);
	*split = new_split;
	return (1);
}

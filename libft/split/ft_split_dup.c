/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:43:35 by tguerin           #+#    #+#             */
/*   Updated: 2022/12/09 22:42:42 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	free_split_until(char **split, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**ft_split_dup(char **split)
{
	char	**copy;
	int		i;

	if (!split)
		return (NULL);
	copy = malloc(sizeof(*copy) * (ft_split_size(split) + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (split[i])
	{
		copy[i] = ft_strdup(split[i]);
		if (!copy[i])
		{
			free_split_until(split, i);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

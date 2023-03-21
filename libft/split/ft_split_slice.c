/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_slice.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:14:37 by tguerin           #+#    #+#             */
/*   Updated: 2023/01/09 15:57:21 by tguerin          ###   ########.fr       */
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

char	**ft_split_slice(char **split, int begin, int end)
{
	char	**copy;
	int		i;

	if (!split)
		return (NULL);
	if (begin < 0 || end < 0 || begin > end || end > ft_split_size(split))
		return (NULL);
	copy = malloc(sizeof(*copy) * (end - begin + 2));
	if (!copy)
		return (NULL);
	i = begin;
	while (split[i] && i <= end)
	{
		copy[i - begin] = ft_strdup(split[i]);
		if (!copy[i - begin])
		{
			free_split_until(split, i);
			return (NULL);
		}
		i++;
	}
	copy[i - begin] = NULL;
	return (copy);
}

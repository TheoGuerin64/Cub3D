/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:59:23 by tguerin           #+#    #+#             */
/*   Updated: 2022/12/15 15:50:35 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_strcasecmp(char *s1, char *s2, int case_sensitive)
{
	size_t	i;
	int		c1;
	int		c2;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (case_sensitive)
		{
			c1 = s1[i];
			c2 = s2[i];
		}
		else
		{
			c1 = ft_tolower(s1[i]);
			c2 = ft_tolower(s2[i]);
		}
		if (c1 != c2)
			return ((unsigned char)c1 - (unsigned char)c2);
		i++;
	}
	return (0);
}

void	ft_split_sort(char **split, int case_sensitive)
{
	char	*tmp;
	int		i;

	i = 0;
	while (split[i + 1])
	{
		if (ft_strcasecmp(split[i], split[i + 1], case_sensitive) > 0)
		{
			tmp = split[i];
			split[i] = split[i + 1];
			split[i + 1] = tmp;
			if (i > 0)
				i--;
		}
		else
			i++;
	}
}

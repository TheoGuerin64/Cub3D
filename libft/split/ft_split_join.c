/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 23:36:08 by tguerin           #+#    #+#             */
/*   Updated: 2022/12/09 23:36:19 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_split_join(char **split, const char *sep)
{
	char	*s;
	int		i;
	int		j;

	s = malloc(sizeof(*s) * (ft_split_len(split)
				+ (ft_split_size(split) - 1) * ft_strlen(sep) + 1));
	if (!s)
		return (NULL);
	s[0] = '\0';
	j = 0;
	i = 0;
	while (split[i])
	{
		ft_strcat(s, split[i]);
		j += ft_strlen(split[i]);
		if (split[i + 1])
		{
			ft_strcat(s, sep);
			j += ft_strlen(sep);
		}
		i++;
	}
	s[j] = '\0';
	return (s);
}

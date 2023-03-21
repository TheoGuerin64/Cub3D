/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:10:22 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/17 12:43:45 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"

int	ft_strcmp_null(const char *s1, const char *s2)
{
	int					i;
	const unsigned char	*str1;
	const unsigned char	*str2;

	if (s1 && !s2)
		return (1);
	i = 0;
	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	while (str1[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

bool	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == 9 || line[i] == ' '))
		i++;
	if (line[i] == 0)
		return (true);
	return (false);
}

bool	is_only_digits(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_free_texture(t_texture texture[NB_TEXTURE])
{
	int	i;

	i = 0;
	while (i < NB_TEXTURE)
	{
		free(texture[i].path);
		i++;
	}
}

void	define_v_texture(char **v_texture)
{
	v_texture[0] = "NO";
	v_texture[1] = "SO";
	v_texture[2] = "WE";
	v_texture[3] = "EA";
	v_texture[4] = "F";
	v_texture[5] = "C";
}

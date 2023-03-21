/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <ltruchel@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:00:31 by ltruchel          #+#    #+#             */
/*   Updated: 2023/02/28 15:06:01 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
#include "../../includes/parsing.h"

static int	get_map_begining(char **scene);
static int	get_map_length(char **scene, int i);

char	**get_map(char **scene)
{
	int		i;
	int		map_i;
	int		len_map;
	char	**map;

	i = get_map_begining(scene);
	len_map = get_map_length(scene, i);
	map = ft_calloc(sizeof(char *), len_map + 1);
	if (!map)
		exit(EXIT_FAILURE);
	map_i = 0;
	while (scene[i] && !is_empty(scene[i]))
	{
		map[map_i] = ft_strdup(scene[i]);
		map_i++;
		i++;
	}
	return (map);
}

static int	get_map_begining(char **scene)
{
	int	i;
	int	cnt_unempty;

	i = 0;
	cnt_unempty = 0;
	while (scene[i])
	{
		if (!is_empty(scene[i]))
		{
			cnt_unempty++;
			if (cnt_unempty == NB_TEXTURE + NB_COLOR)
			{
				i++;
				break ;
			}
		}
		i++;
	}
	while (scene[i] && is_empty(scene[i]))
		i++;
	return (i);
}

static int	get_map_length(char **scene, int i)
{
	int	map_len;

	map_len = 0;
	while (scene[i] && !is_empty(scene[i]))
	{
		map_len++;
		i++;
	}
	return (map_len);
}

static char	*fill_line(char *line, int width)
{
	char	*tmp;

	tmp = ft_strdup(line);
	if (!tmp)
		return (NULL);
	free(line);
	line = ft_calloc(sizeof(char), width + 1);
	ft_memcpy(line, tmp, ft_strlen(tmp));
	ft_memset(line + ft_strlen(tmp), ' ', width - ft_strlen(tmp));
	free(tmp);
	return (line);
}

void	fill_map_space(t_app *app, char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) < app->map_width)
			map[i] = fill_line(map[i], app->map_width);
		i++;
	}
}

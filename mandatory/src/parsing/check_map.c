/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:28:38 by ltruchel          #+#    #+#             */
/*   Updated: 2023/02/28 14:58:45 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
#include "../../includes/parsing.h"

static bool	check_tiles(char **map);
static bool	check_vertical_borders(char **map);

bool	check_map(char **scene)
{
	char	**map;

	map = get_map(scene);
	if (!check_tiles(map))
	{
		ft_split_free(map);
		ft_fprintf(2, "Map does not meet requirements\n");
		return (false);
	}
	if (!check_vertical_borders(map))
	{
		ft_split_free(map);
		ft_fprintf(2, "Map is not surrounded by walls\n");
		return (false);
	}
	if (!check_closed_map(map))
	{
		ft_split_free(map);
		ft_fprintf(2, "Map is not closed\n");
		return (false);
	}
	ft_split_free(map);
	return (true);
}

static bool	check_tiles(char **map)
{
	int	i;
	int	line_i;
	int	cnt_spawn;

	i = -1;
	cnt_spawn = 0;
	while (map[++i])
	{
		line_i = 0;
		while (map[i][line_i])
		{
			if (map[i][line_i] != '0' && map[i][line_i] != '1'
				&& map[i][line_i] != ' '
				&& map[i][line_i] != 'N' && map[i][line_i] != 'S'
				&& map[i][line_i] != 'E' && map[i][line_i] != 'W')
				return (false);
			if (map[i][line_i] == 'N' || map[i][line_i] == 'S'
				|| map[i][line_i] == 'E' || map[i][line_i] == 'W')
				cnt_spawn++;
			line_i++;
		}
	}
	if (cnt_spawn != 1)
		return (false);
	return (true);
}

static bool	check_vertical_borders(char **map)
{
	int	i;
	int	line_i;

	line_i = 0;
	while (map[0][line_i])
	{
		if (map[0][line_i] != '1' && map[0][line_i] != ' ')
			return (false);
		line_i++;
	}
	i = 0;
	while (map[i])
		i++;
	i--;
	line_i = 0;
	while (map[i][line_i])
	{
		if (map[i][line_i] != '1' && map[i][line_i] != ' ')
			return (false);
		line_i++;
	}
	return (true);
}

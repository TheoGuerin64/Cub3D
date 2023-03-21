/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closed_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <ltruchel@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:56:20 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/16 10:40:35 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	replace_spawn(char **map);
static bool	check_line(char **map, int i, int line_i);
static bool	check_column(char **map, int i, int line_i);

bool	check_closed_map(char **map)
{
	int		i;
	int		line_i;

	i = 1;
	replace_spawn(map);
	while (map[i])
	{
		line_i = 0;
		while (map[i][line_i])
		{
			if (map[i][line_i] == '0')
			{
				if (!check_line(map, i, line_i))
					return (false);
				if (!check_column(map, i, line_i))
					return (false);
			}
			line_i++;
		}
		i++;
	}
	return (true);
}

static void	replace_spawn(char **map)
{
	int	i;
	int	line_i;

	i = 0;
	while (map[i])
	{
		line_i = 0;
		while (map[i][line_i])
		{
			if (map[i][line_i] == 'N' || map[i][line_i] == 'S'
				|| map[i][line_i] == 'E' || map[i][line_i] == 'W')
			{
				map[i][line_i] = '0';
				return ;
			}
			line_i++;
		}
		i++;
	}
}

static bool	check_line(char **map, int i, int line_i)
{
	int	start;

	start = line_i;
	while (map[i][line_i] && map[i][line_i] == '0')
		line_i++;
	if (!map[i][line_i] || (map[i][line_i] && map[i][line_i] != '1'))
		return (false);
	while (map[i][start] && map[i][start] == '0')
		start--;
	if (!map[i][start] || (map[i][start] && map[i][start] != '1'))
		return (false);
	return (true);
}

static bool	check_column(char **map, int i, int line_i)
{
	int	start;

	start = i;
	while (map[i][line_i] && map[i][line_i] == '0')
		i++;
	if (!map[i][line_i] || (map[i][line_i] && map[i][line_i] != '1'))
		return (false);
	while (map[start][line_i] && map[start][line_i] == '0')
		start--;
	if (!map[start][line_i] || (map[start][line_i]
		&& map[start][line_i] != '1'))
		return (false);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closed_map_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <ltruchel@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:56:20 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/20 16:37:55 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"

void		replace_tile(char **map, char *to_replace, char replace_by);
static bool	check_line(char **map, int i, int line_i);
static bool	check_column(char **map, int i, int line_i);

bool	check_closed_map(char **map)
{
	int		i;
	int		line_i;

	i = 1;
	replace_tile(map, "NSEWDM", '0');
	replace_tile(map, "Z", '1');
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

void	replace_tile(char **map, char *to_replace, char replace_by)
{
	int	i;
	int	line_i;

	i = 0;
	while (map[i])
	{
		line_i = 0;
		while (map[i][line_i])
		{
			if (ft_strchr(to_replace, map[i][line_i]))
				map[i][line_i] = replace_by;
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

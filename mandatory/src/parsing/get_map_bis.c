/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <ltruchel@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:04:32 by ltruchel          #+#    #+#             */
/*   Updated: 2023/02/28 15:34:13 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
#include "../../includes/parsing.h"

void		set_spawn(char c, int i, int line_i, t_app *app);

void	get_spawn(char **map, t_app *app)
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
				set_spawn(map[i][line_i], i, line_i, app);
			line_i++;
		}
		i++;
	}
}

void	set_spawn(char c, int i, int line_i, t_app *app)
{
	vector_set(&app->player.position, line_i, i);
	if (c == 'N')
	{
		vector_set(&app->player.direction, 0.0, -1.0);
		vector_set(&app->player.plane, FOV, 0.0);
	}
	else if (c == 'S')
	{
		vector_set(&app->player.direction, 0.0, 1.0);
		vector_set(&app->player.plane, -FOV, 0.0);
	}
	else if (c == 'E')
	{
		vector_set(&app->player.direction, 1.0, 0.0);
		vector_set(&app->player.plane, 0.0, FOV);
	}
	else if (c == 'W')
	{
		vector_set(&app->player.direction, -1.0, 0.0);
		vector_set(&app->player.plane, 0.0, -FOV);
	}
}

void	set_map_size(t_app *app, char **map)
{
	int	i;
	int	line_length;
	int	max_line_length;

	i = 0;
	max_line_length = 0;
	while (map[i])
	{
		line_length = ft_strlen(map[i]);
		if (line_length > max_line_length)
			max_line_length = line_length;
		i++;
	}
	app->map_height = i;
	app->map_width = max_line_length;
}

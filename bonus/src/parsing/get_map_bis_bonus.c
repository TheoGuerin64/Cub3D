/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_bis_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <ltruchel@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:04:32 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/20 14:19:37 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"
#include "../../includes/parsing_bonus.h"

void		set_spawn(char c, int i, int line_i, t_app *app);

void	get_spawn_door(char **map, t_app *app)
{
	int	i;
	int	line_i;

	i = 0;
	app->nb_door = 0;
	while (map[i])
	{
		line_i = 0;
		while (map[i][line_i])
		{
			if (map[i][line_i] == 'N' || map[i][line_i] == 'S'
				|| map[i][line_i] == 'E' || map[i][line_i] == 'W')
				set_spawn(map[i][line_i], i, line_i, app);
			if (map[i][line_i])
				app->nb_door++;
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

void	get_misc(t_app *app, char **map)
{
	int	x;
	int	y;

	x = 0;
	app->nb_door = 0;
	app->monster_nb = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'M')
				app->monster_nb++;
			if (map[x][y] == 'D')
				app->nb_door++;
			if (map[x][y] == 'Z')
				ivector_set(&app->exit.pos, y, x);
			y++;
		}
		x++;
	}
}

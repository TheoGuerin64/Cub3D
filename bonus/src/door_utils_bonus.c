/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <ltruchel@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:11:49 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/20 15:56:26 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	define_door_i(t_app *app, int x, int y)
{
	static int	i = 0;

	app->door[i].index = i;
	app->door[i].time = 0;
	app->door[i].state = CLOSED;
	app->door[i].texture_shift = 0;
	app->door[i].pos.x = y;
	app->door[i].pos.y = x;
	i++;
}

bool	define_door(t_app *app)
{
	int	x;
	int	y;

	app->door = malloc(sizeof(t_door) * app->nb_door);
	if (!app->door)
		return (false);
	x = 0;
	while (app->map[x])
	{
		y = 0;
		while (app->map[x][y])
		{
			if (app->map[x][y] == 'D')
				define_door_i(app, x, y);
			y++;
		}
		x++;
	}
	return (true);
}

bool	xpm42_to_array_door(int pixels[256][514], char *path)
{
	xpm_t	*texture;
	int		i;

	texture = mlx_load_xpm42(path);
	if (!texture || (texture->texture.width != DOOR_TEXTURE_WIDTH
			|| texture->texture.height != TEXTURE_SIZE))
	{
		if (texture)
			mlx_delete_xpm42(texture);
		ft_fprintf(2, "Error: Failed to load texture %s\n", path);
		return (false);
	}
	i = 0;
	while (i < DOOR_TEXTURE_WIDTH * TEXTURE_SIZE)
	{
		pixels[i / DOOR_TEXTURE_WIDTH][i % DOOR_TEXTURE_WIDTH] = (
				texture->texture.pixels[i * 4 + 3]
				| texture->texture.pixels[i * 4 + 2] << 8
				| texture->texture.pixels[i * 4 + 1] << 16
				| texture->texture.pixels[i * 4 + 0] << 24);
		i++;
	}
	mlx_delete_xpm42(texture);
	return (true);
}

void	set_door_default(t_app *app)
{
	int	i;

	if (app->nb_door == 0)
		return ;
	i = 0;
	app->door_to_draw = 0;
	while (i < app->nb_door)
	{
		app->door[i].door_raycast_bool = false;
		app->door[i].door_raycast_begin = -1;
		app->door[i].door_raycast_end = -1;
		i++;
	}
}

int	find_door_index(t_app *app)
{
	int	door_index;

	door_index = 0;
	while (door_index < app->nb_door)
	{
		if (app->raycast.map_pos.x == app->door[door_index].pos.x
			&& app->raycast.map_pos.y == app->door[door_index].pos.y)
			return (door_index);
		door_index++;
	}
	return (-1);
}

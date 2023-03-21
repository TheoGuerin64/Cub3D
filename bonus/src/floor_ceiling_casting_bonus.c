/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_casting_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:39:35 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/17 12:43:44 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	calc_floor_wall(t_app *app)
{
	if (app->raycast.side == 0 && app->raycast.ray_dir.x > 0)
	{
		app->raycast.floor_wall.x = app->raycast.map_pos.x;
		app->raycast.floor_wall.y = app->raycast.map_pos.y
			+ app->raycast.wall_x;
	}
	else if (app->raycast.side == 0 && app->raycast.ray_dir.x < 0)
	{
		app->raycast.floor_wall.x = app->raycast.map_pos.x + 1.0;
		app->raycast.floor_wall.y = app->raycast.map_pos.y
			+ app->raycast.wall_x;
	}
	else if (app->raycast.side == 1 && app->raycast.ray_dir.y > 0)
	{
		app->raycast.floor_wall.x = app->raycast.map_pos.x
			+ app->raycast.wall_x;
		app->raycast.floor_wall.y = app->raycast.map_pos.y;
	}
	else
	{
		app->raycast.floor_wall.x = app->raycast.map_pos.x
			+ app->raycast.wall_x;
		app->raycast.floor_wall.y = app->raycast.map_pos.y + 1.0;
	}
}

static void	draw_floor_ceiling(t_app *app, int x, int y)
{
	app->raycast.weight = (WIN_HEIGHT / (2.0 * y - WIN_HEIGHT))
		/ app->raycast.wall_dist;
	if (app->raycast.weight > 1.0)
		app->raycast.weight = 0.0;
	app->raycast.current_floor.x = app->raycast.weight
		* app->raycast.floor_wall.x + (1.0 - app->raycast.weight)
		* app->player.position.x;
	app->raycast.current_floor.y = app->raycast.weight
		* app->raycast.floor_wall.y + (1.0 - app->raycast.weight)
		* app->player.position.y;
	app->raycast.floor_texture.x = ((int)(app->raycast.current_floor.x
				* TEXTURE_SIZE)) % TEXTURE_SIZE;
	app->raycast.floor_texture.y = ((int)(app->raycast.current_floor.y
				* TEXTURE_SIZE)) % TEXTURE_SIZE;
	mlx_put_pixel(app->image, x, y, app->floor_ceiling_texture[0].pixels[
		app->raycast.floor_texture.y][app->raycast.floor_texture.x]);
	mlx_put_pixel(app->image, x, WIN_HEIGHT - y - 1, app->floor_ceiling_texture[
		1].pixels[app->raycast.floor_texture.y][app->raycast.floor_texture.x]);
}

void	floor_ceiling_casting(t_app *app, int x)
{
	int	y;

	calc_floor_wall(app);
	if (app->raycast.draw_end < 0)
		app->raycast.draw_end = WIN_HEIGHT;
	y = app->raycast.draw_end + 1;
	while (y < WIN_HEIGHT)
	{
		draw_floor_ceiling(app, x, y);
		y++;
	}
}

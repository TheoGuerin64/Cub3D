/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:02:28 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/20 16:26:19 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	calcul_pos(t_app *app)
{
	if (app->raycast.side == 0)
		app->raycast.wall_x = app->player.position.y + app->raycast.wall_dist
			* app->raycast.ray_dir.y;
	else
		app->raycast.wall_x = app->player.position.x + app->raycast.wall_dist
			* app->raycast.ray_dir.x;
	app->raycast.wall_x -= floor(app->raycast.wall_x);
	app->raycast.texture.x = (int)(app->raycast.wall_x * (double)TEXTURE_SIZE);
	if (app->raycast.side == 0 && app->raycast.ray_dir.x > 0)
		app->raycast.texture.x = TEXTURE_SIZE - app->raycast.texture.x - 1;
	if (app->raycast.side == 1 && app->raycast.ray_dir.y < 0)
		app->raycast.texture.x = TEXTURE_SIZE - app->raycast.texture.x - 1;
	app->raycast.y_step = 1.0 * TEXTURE_SIZE / app->raycast.line_height;
	app->raycast.texture_pos = (app->raycast.draw_start - (double)WIN_HEIGHT / 2
			+ (double)app->raycast.line_height / 2) * app->raycast.y_step;
}

static void	draw_texture_x(t_app *app, int texture_index, int x)
{
	int	y;

	calcul_pos(app);
	y = app->raycast.draw_start;
	while (y <= app->raycast.draw_end)
	{
		app->raycast.texture.y = (int)app->raycast.texture_pos
			& (TEXTURE_SIZE - 1);
		app->raycast.texture_pos += app->raycast.y_step;
		mlx_put_pixel(app->image, x, y, app->texture[texture_index].pixels[
			app->raycast.texture.y][TEXTURE_SIZE - app->raycast.texture.x - 1]);
		y++;
	}
}

static void	draw_door(t_app *app, int x, t_ivector *door_pos)
{
	int	door_index;

	if (door_pos)
		find_width_door(app, x, door_pos);
	else
	{
		door_index = find_door_index(app);
		select_door_animation(app, x, &app->door[door_index]);
	}
}

void	draw_raycast(t_app *app, int x, t_ivector *door_pos)
{
	app->raycast.line_height = WIN_HEIGHT / app->raycast.wall_dist;
	app->raycast.draw_start = -app->raycast.line_height / 2
		+ app->raycast.half_screen.y;
	if (app->raycast.draw_start < 0)
		app->raycast.draw_start = 0;
	app->raycast.draw_end = app->raycast.line_height / 2
		+ app->raycast.half_screen.y;
	if (app->raycast.draw_end >= WIN_HEIGHT)
		app->raycast.draw_end = WIN_HEIGHT - 1;
	if (app->raycast.map_pos.x == app->anim.pos.x
		&& app->raycast.map_pos.y == app->anim.pos.y)
		draw_animation(app, frame_index_anim(), x);
	else if (app->raycast.map_pos.x == app->exit.pos.x
		&& app->raycast.map_pos.y == app->exit.pos.y && app->monster_nb == 0)
		draw_exit(app, frame_index_exit(), x);
	else if (is_door(app))
		draw_door(app, x, door_pos);
	else
		draw_texture_x(app, texture_index(&app->raycast), x);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:02:28 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/20 17:39:46 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw(t_app *app)
{
	int	x;
	int	y;

	if (!is_valid_pos(app, app->player.position.x, app->player.position.y))
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			x = 0;
			while (x < WIN_WIDTH)
			{
				mlx_put_pixel(app->image, x, y, rgb(0, 0, 0));
				x++;
			}
			y++;
		}
		return ;
	}
	raycasting(app);
}

static void	calcul_pos(t_app *app)
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

static void	draw_texture(t_app *app, int texture_index, int x)
{
	int	y;

	calcul_pos(app);
	y = app->raycast.draw_start;
	while (y <= app->raycast.draw_end)
	{
		app->raycast.texture.y = (int)app->raycast.texture_pos
			& (TEXTURE_SIZE - 1);
		app->raycast.texture_pos += app->raycast.y_step;
		mlx_put_pixel(app->image, x, y, texture_pixel_at(
				&app->texture[texture_index].ptr->texture,
				TEXTURE_SIZE - app->raycast.texture.x - 1,
				app->raycast.texture.y));
		y++;
	}
}

static void	draw_line(t_app *app, int x)
{
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y < app->raycast.draw_start)
			mlx_put_pixel(app->image, x, y, app->ceiling_color);
		else if (y > app->raycast.draw_end)
			mlx_put_pixel(app->image, x, y, app->floor_color);
		y++;
	}
	draw_texture(app, texture_index(&app->raycast), x);
}

void	draw_raycast(t_app *app, int x)
{
	app->raycast.line_height = WIN_HEIGHT / app->raycast.wall_dist;
	app->raycast.draw_start = -app->raycast.line_height / 2 + WIN_HEIGHT / 2;
	if (app->raycast.draw_start < 0)
		app->raycast.draw_start = 0;
	app->raycast.draw_end = app->raycast.line_height / 2 + WIN_HEIGHT / 2;
	if (app->raycast.draw_end >= WIN_HEIGHT)
		app->raycast.draw_end = WIN_HEIGHT - 1;
	draw_line(app, x);
}

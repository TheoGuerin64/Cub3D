/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_draw_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <ltruchel@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:38:09 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/17 13:55:35 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	draw_door_full(t_app *app, int x)
{
	int	y;

	calcul_pos(app);
	y = app->raycast.draw_start;
	while (y <= app->raycast.draw_end)
	{
		app->raycast.texture.y = (int)app->raycast.texture_pos
			& (TEXTURE_SIZE - 1);
		app->raycast.texture_pos += app->raycast.y_step;
		mlx_put_pixel(app->image, x, y, app->door_full.pixels[
			app->raycast.texture.y][app->raycast.texture.x]);
		y++;
	}
}

static void	animate_door(t_app *app, int x, int shift, int doorpart)
{	
	int				color;
	int				y;

	calcul_pos(app);
	y = app->raycast.draw_start;
	while (y <= app->raycast.draw_end)
	{
		app->raycast.texture.y = (int)app->raycast.texture_pos
			& (TEXTURE_SIZE - 1);
		app->raycast.texture_pos += app->raycast.y_step;
		color = app->door_part[doorpart].pixels[
			app->raycast.texture.y][app->raycast.texture.x + shift];
		if (alpha(color) > 0)
			mlx_put_pixel(app->image, x, y,
				app->door_part[doorpart].pixels[
				app->raycast.texture.y][app->raycast.texture.x + shift]);
		y++;
	}
}

static void	set_shift(t_app *app, t_door *door)
{
	if (door->state == OPENING || door->state == CLOSING)
	{
		if (mlx_get_time() - door->time > DOOR_FRAME_TIME)
		{
			door->time = mlx_get_time();
			door->texture_shift += 2.5;
		}
		if (door->texture_shift >= 200 && door->state == OPENING)
		{
			door->texture_shift = 0;
			door->time = 0;
			app->map[door->pos.y][door->pos.x] = 'd';
			door->state = OPEN;
			minimap(app);
		}
		else if (door->texture_shift >= 180 && door->state == CLOSING)
		{
			door->texture_shift = 0;
			door->time = 0;
			door->state = CLOSED;
			minimap(app);
		}
	}
}

void	set_shift_all_doors(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->nb_door)
	{
		set_shift(app, &app->door[i]);
		i++;
	}
}

void	select_door_animation(t_app *app, int x, t_door *door)
{
	if (door->state == CLOSED)
		draw_door_full(app, x);
	else
	{
		if (door->state == OPENING)
		{
			animate_door(app, x, -(door->texture_shift - 255), DOOR_LEFT);
			animate_door(app, x, door->texture_shift + 0, DOOR_RIGHT);
		}
		else if (door->state == CLOSING)
		{
			animate_door(app, x, door->texture_shift + 80, DOOR_LEFT);
			animate_door(app, x, -(door->texture_shift - 178), DOOR_RIGHT);
		}
	}
}

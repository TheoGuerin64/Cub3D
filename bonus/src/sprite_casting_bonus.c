/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:44:29 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/20 14:31:36 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	sort_sprites(int *order, double *dist, int amount)
{
	double	tmp_dist;
	int		tmp;
	int		i;
	int		j;

	i = 0;
	while (i < amount - 1)
	{
		j = i + 1;
		while (j < amount)
		{
			if (dist[i] < dist[j])
			{
				tmp_dist = dist[i];
				dist[i] = dist[j];
				dist[j] = tmp_dist;
				tmp = order[i];
				order[i] = order[j];
				order[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	order_sprites(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->monster_nb)
	{
		app->raycast.sprite_order[i] = i;
		app->raycast.sprite_distance[i] = ((app->player.position.x
					- app->monster[i].position.x) * (app->player.position.x
					- app->monster[i].position.x) + (app->player.position.y
					- app->monster[i].position.y) * (app->player.position.y
					- app->monster[i].position.y));
		i++;
	}
	sort_sprites(app->raycast.sprite_order, app->raycast.sprite_distance,
		app->monster_nb);
}

static void	calc_draw_start_end(t_app *app, t_ivector *draw_start,
	t_ivector *draw_end)
{
	draw_start->y = -app->raycast.sprite_size.y / 2 + WIN_HEIGHT / 2
		+ app->raycast.v_move_screen;
	draw_start->y = fmax(draw_start->y, 0);
	draw_end->y = app->raycast.sprite_size.y / 2 + WIN_HEIGHT / 2
		+ app->raycast.v_move_screen;
	draw_end->y = fmin(draw_end->y, WIN_HEIGHT - 1);
	draw_start->x = -app->raycast.sprite_size.x / 2
		+ app->raycast.sprite_screen_x;
	if (draw_start->x < 0)
		draw_start->x = 0;
	draw_end->x = app->raycast.sprite_size.x / 2 + app->raycast.sprite_screen_x;
	if (draw_end->x >= WIN_WIDTH)
		draw_end->x = WIN_WIDTH - 1;
}

static void	draw_sprite(t_app *app, t_ivector *draw_start, t_ivector *draw_end,
	int i)
{
	int	color;
	int	y;

	app->raycast.texture.x = calcul_texture_x(app);
	if (is_sprite_visible(app))
	{
		app->monster[app->raycast.sprite_order[i]].is_visible = true;
		app->monster[app->raycast.sprite_order[i]].transform_x
			= app->raycast.transform.x;
		y = draw_start->y;
		while (y < draw_end->y)
		{
			app->raycast.texture.y = ((((y - app->raycast.v_move_screen) * 256
							- WIN_HEIGHT * 128 + app->raycast.sprite_size.y
							* 128) * TEXTURE_SIZE) / app->raycast.sprite_size.y)
				/ 256;
			if (app->raycast.texture.y < 0)
				app->raycast.texture.y = 0;
			color = app->monster_texture.pixels[
				app->raycast.texture.y][app->raycast.texture.x];
			if (alpha(color) > 0)
				mlx_put_pixel(app->image, app->raycast.stripe, y, color);
			y++;
		}
	}
}

void	sprite_casting(t_app *app)
{
	t_ivector	draw_start;
	t_ivector	draw_end;
	int			i;

	order_sprites(app);
	i = 0;
	while (i < app->monster_nb)
	{
		calcul_monster_pos(app, i);
		calc_draw_start_end(app, &draw_start, &draw_end);
		app->raycast.stripe = draw_start.x;
		app->monster[app->raycast.sprite_order[i]].is_visible = false;
		while (app->raycast.stripe < draw_end.x)
		{
			draw_sprite(app, &draw_start, &draw_end, i);
			app->raycast.stripe++;
		}
		i++;
	}
}

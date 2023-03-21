/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:27:46 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/20 16:37:20 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	draw_square(t_app *app, t_ivector pos, int len, int color)
{
	int			y_base_value;
	t_ivector	sum_pos_len;

	y_base_value = pos.y;
	ivector_set(&sum_pos_len, pos.x + len, pos.y + len);
	while (pos.x != sum_pos_len.x)
	{
		ivector_set(&pos, pos.x, y_base_value);
		while (pos.y != sum_pos_len.y)
		{
			mlx_put_pixel(app->image_hud, pos.x + MINIMAP_X,
				pos.y + MINIMAP_Y, color);
			ivector_set(&pos, pos.x, pos.y + 1);
		}
		ivector_set(&pos, pos.x + 1, pos.y);
	}
}

static void	draw_cols_minimap(t_app *app, t_minimap *minimap)
{
	if (!is_valid_pos(app, minimap->map_start.x, minimap->map_start.y, "1 "))
		draw_square(app, minimap->map_pos, SQUARE_LEN, C_WALL);
	else if (!is_valid_pos(app, minimap->map_start.x,
			minimap->map_start.y, "D"))
		draw_square(app, minimap->map_pos, SQUARE_LEN, C_CLOSED_DOOR);
	else if (!is_valid_pos(app, minimap->map_start.x,
			minimap->map_start.y, "d"))
		draw_square(app, minimap->map_pos, SQUARE_LEN, C_OPEN_DOOR);
	else if (!is_valid_pos(app, minimap->map_start.x,
			minimap->map_start.y, "Z"))
		if (app->monster_nb == 0)
			draw_square(app, minimap->map_pos, SQUARE_LEN, C_EXIT);
	else
		draw_square(app, minimap->map_pos, SQUARE_LEN, C_WALL);
	else
		draw_square(app, minimap->map_pos, SQUARE_LEN, C_OPEN);
	ivector_set(&minimap->map_pos, minimap->map_pos.x,
		minimap->map_pos.y + SQUARE_LEN);
	ivector_set(&minimap->map_start, minimap->map_start.x,
		minimap->map_start.y + 1);
}

static void	draw_minimap(t_app *app, t_minimap *minimap)
{
	int			y_base_value;

	y_base_value = minimap->map_start.y;
	while (minimap->map_start.x <= minimap->map_end.x)
	{
		ivector_set(&minimap->map_start, minimap->map_start.x, y_base_value);
		ivector_set(&minimap->map_pos, minimap->map_pos.x, 0);
		while (minimap->map_start.y <= minimap->map_end.y)
			draw_cols_minimap(app, minimap);
		ivector_set(&minimap->map_pos, minimap->map_pos.x + SQUARE_LEN,
			minimap->map_pos.y);
		ivector_set(&minimap->map_start, minimap->map_start.x + 1,
			minimap->map_start.y);
	}
}

void	minimap(t_app *app)
{
	t_minimap	minimap;

	ivector_set(&minimap.map_pos, 0, 0);
	ivector_set(&minimap.map_start, (int)app->player.position.x - 10,
		(int)app->player.position.y - 5);
	ivector_set(&minimap.map_end, (int)app->player.position.x + 10,
		(int)app->player.position.y + 5);
	draw_minimap(app, &minimap);
	draw_arrow(app);
}

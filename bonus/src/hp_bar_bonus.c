/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hp_bar_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:43:18 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/17 14:49:40 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	draw_hp_background(t_app *app)
{
	int	x;
	int	y;

	x = (HP_BAR_WIDTH / BASE_HP - HP_BAR_OFFSET - 4);
	while (x < HP_BAR_WIDTH)
	{
		y = 0;
		while (y < HP_BAR_HEIGHT)
		{
			mlx_put_pixel(app->image_hud, x + HP_BAR_X, y + HP_BAR_Y,
				C_HP_BAR_BG);
			y++;
		}
		x++;
	}
}

void	draw_hp_bar(t_app *app)
{
	int	x;
	int	y;
	int	hp;

	draw_hp_background(app);
	hp = 1;
	while (hp <= app->player.hp)
	{
		x = HP_BAR_WIDTH / BASE_HP;
		while (x < (HP_BAR_WIDTH / BASE_HP) * hp - HP_BAR_OFFSET)
		{
			y = HP_BAR_OFFSET;
			while (y < HP_BAR_HEIGHT - HP_BAR_OFFSET)
			{
				mlx_put_pixel(app->image_hud, x + HP_BAR_X, y + HP_BAR_Y,
					C_HP_CURRENT);
				y++;
			}
			x++;
		}
		hp++;
	}
}

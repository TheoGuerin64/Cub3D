/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:03:45 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/18 14:07:15 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	frame_index_anim(void)
{
	static int		i = 0;
	static double	delta_time;

	if (mlx_get_time() - delta_time > 3 && i == 0)
	{
		delta_time = mlx_get_time();
		i++;
		return (i);
	}
	else if (mlx_get_time() - delta_time > 0.035 && i != 0)
	{
		delta_time = mlx_get_time();
		i++;
		if (i >= NB_FRAME)
			i = 0;
		return (i);
	}
	return (i);
}

void	draw_animation(t_app *app, int frame_index, int x)
{
	int	y;

	calcul_pos(app);
	y = app->raycast.draw_start;
	while (y <= app->raycast.draw_end)
	{
		app->raycast.texture.y = (int)app->raycast.texture_pos
			& (TEXTURE_SIZE - 1);
		app->raycast.texture_pos += app->raycast.y_step;
		mlx_put_pixel(app->image, x, y, app->anim.frame[frame_index].pixels[
			app->raycast.texture.y][app->raycast.texture.x]);
		y++;
	}
}

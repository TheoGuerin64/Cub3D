/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:44:29 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/17 12:43:45 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	calcul_monster_pos(t_app *app, int i)
{
	app->raycast.sprite.x = app->monster[
		app->raycast.sprite_order[i]].position.x - app->player.position.x;
	app->raycast.sprite.y = app->monster[
		app->raycast.sprite_order[i]].position.y - app->player.position.y;
	app->raycast.inv_det = 1.0 / (app->player.plane.x * app->player.direction.y
			- app->player.direction.x * app->player.plane.y);
	app->raycast.transform.x = app->raycast.inv_det
		* (app->player.direction.y * app->raycast.sprite.x
			- app->player.direction.x * app->raycast.sprite.y);
	app->raycast.transform.y = app->raycast.inv_det * (-app->player.plane.y
			* app->raycast.sprite.x + app->player.plane.x
			* app->raycast.sprite.y);
	app->raycast.sprite_screen_x = (int)((WIN_WIDTH / 2)
			* (1 + app->raycast.transform.x / app->raycast.transform.y));
	app->raycast.v_move_screen = (int)(VMOVE / app->raycast.transform.y);
	app->raycast.sprite_size.y = abs((int)(WIN_HEIGHT
				/ app->raycast.transform.y)) / VDIV;
	app->raycast.sprite_size.x = abs((int)(WIN_HEIGHT
				/ (app->raycast.transform.y))) / UDIV;
}

int	calcul_texture_x(t_app *app)
{
	return ((256 * (app->raycast.stripe - (-app->raycast.sprite_size.x / 2
					+ app->raycast.sprite_screen_x)) * TEXTURE_SIZE
			/ app->raycast.sprite_size.x) / 256);
}

bool	is_sprite_visible(t_app *app)
{
	return (app->raycast.transform.y > 0 && app->raycast.stripe > 0
		&& app->raycast.stripe < WIN_WIDTH && app->raycast.transform.y
		< app->raycast.z_buffer[app->raycast.stripe]);
}

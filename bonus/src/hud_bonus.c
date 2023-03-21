/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:01:37 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/20 14:13:51 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	draw_gun(t_app *app, int frame)
{
	draw_texture(app->image_hud, &app->gun_texture[frame]->texture,
		WIN_WIDTH - app->gun_texture[frame]->texture.width - GUN_OFFSET,
		WIN_HEIGHT - app->gun_texture[frame]->texture.height);
}

void	update_gun(t_app *app)
{
	double	time;
	int		frame;

	time = mlx_get_time();
	if (time - app->player.last_shoot < GUN_FRAME_TIME * GUN_NB_FRAME)
		frame = (int)((time - app->player.last_shoot) / GUN_FRAME_TIME);
	else
		frame = 5;
	draw_gun(app, frame);
	draw_hp_bar(app);
}

bool	draw_crosshair(t_app *app)
{
	xpm_t	*texture;

	texture = mlx_load_xpm42(CROSSHAIR_PATH);
	if (!texture)
	{
		printf("Error: Failed to load texture %s\n", CROSSHAIR_PATH);
		return (false);
	}
	draw_texture(app->image_hud, &texture->texture,
		app->raycast.half_screen.x - CROSSHAIR_SIZE / 2,
		app->raycast.half_screen.y - CROSSHAIR_SIZE / 2);
	mlx_delete_xpm42(texture);
	return (true);
}

void	show_end_screen(t_app *app, char *outcome_path)
{
	static bool	load_game_over = false;
	xpm_t		*texture;

	if (load_game_over == false)
	{
		texture = mlx_load_xpm42(outcome_path);
		if (!texture || (texture->texture.width != WIN_WIDTH
				|| texture->texture.height != WIN_HEIGHT))
		{
			if (texture)
				mlx_delete_xpm42(texture);
			printf("Error: Failed to load texture %s\n", outcome_path);
			mlx_close_window(app->mlx);
			return ;
		}
		draw_texture(app->image_hud, &texture->texture, 0, 0);
		mlx_delete_xpm42(texture);
		load_game_over = true;
	}
}

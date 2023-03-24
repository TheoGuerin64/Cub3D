/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:14:18 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/24 18:08:41 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static bool	get_textures(t_app *app)
{
	int	i;

	i = 0;
	while (i < NB_TEXTURE)
	{
		app->texture[i].ptr = mlx_load_xpm42(app->texture[i].path);
		if (!app->texture[i].ptr
			|| app->texture[i].ptr->texture.width != TEXTURE_SIZE
			|| app->texture[i].ptr->texture.height != TEXTURE_SIZE)
		{
			if (app->texture[i].ptr)
				mlx_delete_xpm42(app->texture[i].ptr);
			while (i > 0)
			{
				i--;
				if (app->texture[i].ptr)
					mlx_delete_xpm42(app->texture[i].ptr);
			}
			return (false);
		}
		i++;
	}
	return (true);
}

static void	hook(void *param)
{
	t_app		*app;

	app = (t_app *)param;
	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(app->mlx);
	if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT))
		rotate_player(app, 1);
	if (mlx_is_key_down(app->mlx, MLX_KEY_RIGHT))
		rotate_player(app, -1);
	if (mlx_is_key_down(app->mlx, MLX_KEY_A))
		move_player(app, 1, 0);
	if (mlx_is_key_down(app->mlx, MLX_KEY_D))
		move_player(app, -1, 0);
	if (mlx_is_key_down(app->mlx, MLX_KEY_W))
		move_player(app, 0, 1);
	if (mlx_is_key_down(app->mlx, MLX_KEY_S))
		move_player(app, 0, -1);
	draw(app);
}

bool	create_window(t_app *app)
{
	app->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, true);
	if (!app->mlx)
		return (false);
	app->image = mlx_new_image(app->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!app->image)
	{
		mlx_terminate(app->mlx);
		return (false);
	}
	if (mlx_image_to_window(app->mlx, app->image, 0, 0) == -1
		|| !get_textures(app))
	{
		mlx_delete_image(app->mlx, app->image);
		mlx_terminate(app->mlx);
		return (false);
	}
	mlx_set_cursor_mode(app->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(app->mlx, &hook, app);
	return (true);
}

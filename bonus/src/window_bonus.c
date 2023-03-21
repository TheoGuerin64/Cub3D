/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:14:18 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/20 16:35:15 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	handle_mouse(t_app *app)
{
	static bool	hold = false;
	int			x;
	int			y;

	if (mlx_is_mouse_down(app->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (!hold)
		{
			shoot(app);
			if (!hold)
				hold = true;
		}
	}
	else
		hold = false;
	mlx_get_mouse_pos(app->mlx, &x, &y);
	if (x != app->raycast.half_screen.x)
	{
		rotate_player(app, (app->raycast.half_screen.x - x) * SENSITIVITY);
		mlx_set_mouse_pos(app->mlx, app->raycast.half_screen.x,
			app->raycast.half_screen.y);
	}
}

static void	handle_keyboard(t_app *app)
{
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
	if (mlx_is_key_down(app->mlx, MLX_KEY_E))
		open_door(app);
}

static void	loop(void *param)
{
	t_app		*app;

	app = (t_app *)param;
	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(app->mlx);
	if (!app->lose && !app->win)
	{
		handle_keyboard(app);
		handle_mouse(app);
		raycasting(app);
		update_gun(app);
		monsters_follow_player(app);
		win_condition(app);
	}
	else if (app->lose)
		show_end_screen(app, LOSE_PATH);
	else
		show_end_screen(app, WIN_PATH);
}

static bool	create_images(t_app *app)
{
	app->image = mlx_new_image(app->mlx, WIN_WIDTH, WIN_HEIGHT);
	app->image_hud = mlx_new_image(app->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!app->image || !app->image_hud)
	{
		ft_putstr_fd("cub3d: failed to create image\n", 2);
		return (false);
	}
	if (mlx_image_to_window(app->mlx, app->image, 0, 0) == -1
		|| mlx_image_to_window(app->mlx, app->image_hud, 0, 0) == -1)
	{
		ft_putstr_fd("cub3d: failed to put image to window\n", 2);
		return (false);
	}
	return (true);
}

bool	create_window(t_app *app)
{
	app->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, true);
	if (!app->mlx)
	{
		ft_putstr_fd("cub3d: failed to create window\n", 2);
		return (false);
	}
	if (!create_images(app) || !draw_crosshair(app) || !load_textures(app))
	{
		mlx_terminate(app->mlx);
		return (false);
	}
	app->icon = mlx_load_xpm42(MONSTER_PATH);
	if (!app->icon)
	{
		ft_putstr_fd("cub3d: failed to load icon\n", 2);
		return (false);
	}
	mlx_set_icon(app->mlx, &app->icon->texture);
	mlx_delete_xpm42(app->icon);
	mlx_set_cursor_mode(app->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(app->mlx, &loop, app);
	mlx_set_mouse_pos(app->mlx, app->raycast.half_screen.x,
		app->raycast.half_screen.y);
	return (true);
}

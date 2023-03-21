/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <ltruchel@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:38:09 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/20 16:36:10 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	frame_index_exit(void)
{
	static int		i = 0;
	static double	delta_time;

	if (mlx_get_time() - delta_time > EXIT_FRAME_DURATION)
	{
		delta_time = mlx_get_time();
		i++;
		if (i == NB_EXIT_TEXTURE)
			i = 0;
		return (i);
	}
	return (i);
}

void	draw_exit(t_app *app, int frame_index, int x)
{
	int	y;

	calcul_pos(app);
	y = app->raycast.draw_start;
	while (y <= app->raycast.draw_end)
	{
		app->raycast.texture.y = (int)app->raycast.texture_pos
			& (TEXTURE_SIZE - 1);
		app->raycast.texture_pos += app->raycast.y_step;
		mlx_put_pixel(app->image, x, y, app->exit_texture[frame_index].pixels[
			app->raycast.texture.y][app->raycast.texture.x]);
		y++;
	}
}

void	win_condition(t_app *app)
{
	static bool	change_exit_wall = false;

	if (app->monster_nb == 0 && change_exit_wall == false)
	{
		app->map[app->exit.pos.y][app->exit.pos.x] = 'Z';
		minimap(app);
		change_exit_wall = true;
	}
	if (app->monster_nb == 0 && sqrt(pow(app->player.position.x
				- (app->exit.pos.x + 0.5), 2) + pow(app->player.position.y
				- (app->exit.pos.y + 0.5), 2)) < EXIT_RANGE)
		app->win = true;
}

bool	load_exit_texture(t_app *app)
{
	int		i;
	char	path[28];
	char	nb[2];

	ft_strlcpy(path, EXIT_TEXTURE_PATH, 21);
	nb[1] = '\0';
	i = 0;
	while (i < NB_EXIT_TEXTURE)
	{
		nb[0] = i % 10 + '0';
		ft_strlcpy(path + 20, nb, 2);
		ft_strlcat(path + 20, ".xpm42", 8);
		if (!xpm42_to_array(app->exit_texture[i].pixels, path))
			return (false);
		i++;
	}
	return (true);
}

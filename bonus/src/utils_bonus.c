/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:47:05 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/20 18:10:09 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

bool	is_in_map(t_app *app, int x, int y)
{
	return (x >= 0 && x < app->map_width && y >= 0 && y < app->map_height);
}

bool	is_valid_pos(t_app *app, int x, int y, char *set)
{
	return (is_in_map(app, x, y) && !ft_strchr(set, app->map[y][x]));
}

void	delete_gun_xpm(t_app *app, int until)
{
	int	i;

	i = 0;
	while (i < until)
	{
		mlx_delete_xpm42(app->gun_texture[i]);
		i++;
	}
}

void	free_monsters(t_app *app)
{
	free(app->monster);
	free(app->raycast.sprite_order);
	free(app->raycast.sprite_distance);
}

void	change_tile_door(t_app *app, char c)
{
	int	i;

	if (app->nb_door == 0)
		return ;
	i = 0;
	while (i < app->nb_door)
	{
		if (app->door[i].state != OPEN && app->door[i].state != CLOSED)
			app->map[app->door[i].pos.y][app->door[i].pos.x] = c;
		i++;
	}
}

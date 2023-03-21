/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:47:05 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/01 19:40:28 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

bool	is_in_map(t_app *app, int x, int y)
{
	return (x >= 0 && x < app->map_width && y >= 0 && y < app->map_height);
}

bool	is_valid_pos(t_app *app, int x, int y)
{
	return (is_in_map(app, x, y)
		&& app->map[y][x] != '1' && app->map[y][x] != ' ');
}

int	texture_index(t_raycast *raycast)
{
	if (raycast->side == 0)
	{
		if (raycast->ray_dir.x > 0)
			return (0);
		else
			return (3);
	}
	else
	{
		if (raycast->ray_dir.y > 0)
			return (2);
		else
			return (1);
	}
}

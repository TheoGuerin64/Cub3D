/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_open_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <ltruchel@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:48:58 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/17 12:43:44 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	open_door(t_app *app)
{
	int	door_index;

	middle_raycast(app, "1Dd");
	if (is_door(app))
	{
		door_index = find_door_index(app);
		if (app->door[door_index].state == CLOSED
			&& app->raycast.wall_dist < DOOR_OPENING_DIST)
		{
			system("paplay "DOOR_SFX" &");
			app->door[door_index].state = OPENING;
		}
		else if (app->door[door_index].state == OPEN
			&& app->raycast.wall_dist < DOOR_OPENING_DIST)
		{
			system("paplay "DOOR_SFX" &");
			app->map[app->door[door_index].pos.y][
				app->door[door_index].pos.x] = 'D';
			app->door[door_index].state = CLOSING;
		}
	}
}

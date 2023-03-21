/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_raycast_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <ltruchel@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:38:46 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/20 14:01:14 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	calcul_step(t_raycast *raycast, t_player *player);
void	init_dda(t_raycast *raycast, t_player *player, int x);
void	dda_to_hit(t_app *app, t_raycast *raycast, char ***map, char *to_hit);

static void	raycast_behind_door(t_app *app, int x)
{
	int	i;

	change_tile_door(app, 'd');
	i = 0;
	while (i < app->door_to_draw)
	{
		x = app->door[i].door_raycast_begin;
		while (x <= app->door[i].door_raycast_end)
		{	
			init_dda(&app->raycast, &app->player, x);
			calcul_step(&app->raycast, &app->player);
			dda_to_hit(app, &app->raycast, &app->map, "1DZ");
			app->raycast.z_buffer[x] = app->raycast.wall_dist;
			draw_raycast(app, x, NULL);
			floor_ceiling_casting(app, x);
			x++;
		}
		i++;
	}
}

static void	raycast_on_door(t_app *app, int x)
{
	int	i;

	change_tile_door(app, 'D');
	i = 0;
	while (i < app->door_to_draw)
	{
		x = app->door[i].door_raycast_begin;
		while (x <= app->door[i].door_raycast_end)
		{	
			init_dda(&app->raycast, &app->player, x);
			calcul_step(&app->raycast, &app->player);
			dda_to_hit(app, &app->raycast, &app->map, "1D");
			app->raycast.z_buffer[x] = app->raycast.wall_dist;
			draw_raycast(app, x, NULL);
			x++;
		}
		i++;
	}
}

void	launch_door_raycast(t_app *app, int x)
{
	raycast_behind_door(app, x);
	raycast_on_door(app, x);
}

void	find_width_door(t_app *app, int x, t_ivector *door_pos)
{
	if (app->door->index >= app->door_to_draw
		&& app->door[app->door_to_draw].door_raycast_bool == false
		&& (door_pos->x != app->raycast.map_pos.x
			|| door_pos->y != app->raycast.map_pos.y))
	{
		ivector_set(door_pos, app->raycast.map_pos.x, app->raycast.map_pos.y);
		app->door[app->door_to_draw].door_raycast_begin = x;
		app->door[app->door_to_draw].door_raycast_bool = true;
		app->door_to_draw++;
	}
	else
		app->door[app->door_to_draw - 1].door_raycast_end = x;
}

bool	is_door(t_app *app)
{
	int	i;

	if (app->nb_door == 0)
		return (false);
	i = 0;
	while (i < app->nb_door)
	{
		if (app->raycast.map_pos.x == app->door[i].pos.x
			&& app->raycast.map_pos.y == app->door[i].pos.y)
			return (true);
		i++;
	}
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:22:58 by tguerin           #+#    #+#             */
/*   Updated: 2023/02/16 18:22:20 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	init_dda(t_raycast *raycast, t_player *player, int x)
{
	ivector_set(&raycast->step, 0, 0);
	vector_set(&raycast->side_dist, 0.0, 0.0);
	ivector_set(&raycast->map_pos, player->position.x, player->position.y);
	raycast->camera_x = 2.0 * x / WIN_WIDTH - 1.0;
	raycast->ray_dir.x = player->direction.x
		+ player->plane.x * raycast->camera_x;
	raycast->ray_dir.y = player->direction.y
		+ player->plane.y * raycast->camera_x;
	if (raycast->ray_dir.x == 0.0)
		raycast->delta_dist.x = INFINITY;
	else
		raycast->delta_dist.x = ft_dabs(1.0 / raycast->ray_dir.x);
	if (raycast->ray_dir.y == 0.0)
		raycast->delta_dist.y = INFINITY;
	else
		raycast->delta_dist.y = ft_dabs(1.0 / raycast->ray_dir.y);
}

static void	calcul_step(t_raycast *raycast, t_player *player)
{
	if (raycast->ray_dir.x < 0.0)
	{
		raycast->step.x = -1;
		raycast->side_dist.x = (player->position.x - raycast->map_pos.x)
			* raycast->delta_dist.x;
	}
	else
	{
		raycast->step.x = 1;
		raycast->side_dist.x = (raycast->map_pos.x + 1.0 - player->position.x)
			* raycast->delta_dist.x;
	}
	if (raycast->ray_dir.y < 0.0)
	{
		raycast->step.y = -1;
		raycast->side_dist.y = (player->position.y - raycast->map_pos.y)
			* raycast->delta_dist.y;
	}
	else
	{
		raycast->step.y = 1;
		raycast->side_dist.y = (raycast->map_pos.y + 1.0 - player->position.y)
			* raycast->delta_dist.y;
	}
}

static void	dda(t_raycast *raycast, char ***map)
{
	raycast->hit = false;
	while (!raycast->hit)
	{
		if (raycast->side_dist.x < raycast->side_dist.y)
		{
			raycast->side_dist.x += raycast->delta_dist.x;
			raycast->map_pos.x += raycast->step.x;
			raycast->side = 0;
		}
		else
		{
			raycast->side_dist.y += raycast->delta_dist.y;
			raycast->map_pos.y += raycast->step.y;
			raycast->side = 1;
		}
		if ((*map)[raycast->map_pos.y][raycast->map_pos.x] == '1')
			raycast->hit = true;
	}
	if (raycast->side == 0)
		raycast->wall_dist = raycast->side_dist.x - raycast->delta_dist.x;
	else
		raycast->wall_dist = raycast->side_dist.y - raycast->delta_dist.y;
}

void	raycasting(t_app *app)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_dda(&app->raycast, &app->player, x);
		calcul_step(&app->raycast, &app->player);
		dda(&app->raycast, &app->map);
		draw_raycast(app, x);
		x += 1;
	}
}

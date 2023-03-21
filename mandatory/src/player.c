/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:00:52 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/02 19:41:13 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_player(t_app *app)
{
	if (app->player.plane.x != 0)
		app->player.plane.x *= M_PI / 180;
	else
		app->player.plane.y *= M_PI / 180;
	app->player.position.x += 0.5;
	app->player.position.y += 0.5;
}

void	move_player(t_app *app, int dx, int dy)
{
	if (dy)
	{
		app->player.position.x += app->player.direction.x * SPEED * dy;
		app->player.position.y += app->player.direction.y * SPEED * dy;
	}
	else if (dx)
	{
		app->player.position.x += app->player.direction.y * SPEED * dx;
		app->player.position.y += app->player.direction.x * SPEED * -dx;
	}
}

void	rotate_player(t_app *app, int direction)
{
	t_matrix	rotation;

	rotation.a = cos(ROTATION_SPEED * direction);
	rotation.b = sin(ROTATION_SPEED * direction);
	rotation.c = -sin(ROTATION_SPEED * direction);
	rotation.d = cos(ROTATION_SPEED * direction);
	vector_rotate(&rotation, &app->player.direction);
	vector_rotate(&rotation, &app->player.plane);
}

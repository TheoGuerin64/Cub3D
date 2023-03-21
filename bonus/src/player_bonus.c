/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:00:52 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/20 14:03:05 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	init_player(t_app *app)
{
	if (app->player.plane.x != 0)
		app->player.plane.x *= M_PI / 180;
	else
		app->player.plane.y *= M_PI / 180;
	app->player.position.x += 0.5;
	app->player.position.y += 0.5;
	app->player.last_shoot = 0.0;
	app->player.hp = BASE_HP;
	app->lose = false;
	app->win = false;
}

void	move_player(t_app *app, int dx, int dy)
{
	t_vector	step;

	if (dy)
	{
		step.x = app->player.direction.x * MOVE_SPEED * dy;
		step.y = app->player.direction.y * MOVE_SPEED * dy;
	}
	else if (dx)
	{
		step.x = app->player.direction.y * MOVE_SPEED * dx;
		step.y = app->player.direction.x * MOVE_SPEED * -dx;
	}
	if (!ft_strchr("1DZ", app->map[(int)app->player.position.y]
			[(int)(app->player.position.x + step.x)]))
		app->player.position.x += step.x;
	if (!ft_strchr("1DZ", app->map[(int)(app->player.position.y + step.y)]
		[(int)app->player.position.x]))
		app->player.position.y += step.y;
	minimap(app);
}

void	rotate_player(t_app *app, double angle)
{
	t_matrix	rotation;

	rotation.a = cos(ROTATION_SPEED * angle);
	rotation.b = sin(ROTATION_SPEED * angle);
	rotation.c = -sin(ROTATION_SPEED * angle);
	rotation.d = cos(ROTATION_SPEED * angle);
	vector_rotate(&rotation, &app->player.direction);
	vector_rotate(&rotation, &app->player.plane);
	minimap(app);
}

bool	player_hit(t_app *app, int monster_index)
{
	remove_monster(app, monster_index);
	app->player.hp -= 1;
	if (app->player.hp == 1)
	{
		system("paplay ./bonus/assets/player_death.ogg &");
		app->lose = true;
		return (true);
	}
	draw_hp_bar(app);
	system("paplay ./bonus/assets/hurt.ogg &");
	return (false);
}

void	shoot(t_app *app)
{
	double	time;
	int		monster_index;
	int		i;

	time = mlx_get_time();
	if (app->player.last_shoot == 0.0 || app->player.last_shoot
		+ SHOOT_WAIT < time)
	{
		app->player.last_shoot = time;
		system("paplay "GUNSHOT_PATH" &");
		i = 0;
		while (i < app->monster_nb)
		{
			monster_index = app->raycast.sprite_order[app->monster_nb - i - 1];
			if (app->monster[monster_index].is_visible
				&& fabs(app->monster[monster_index].transform_x) <= 0.25)
			{
				monster_hit(app, monster_index);
				break ;
			}
			i++;
		}
	}
}

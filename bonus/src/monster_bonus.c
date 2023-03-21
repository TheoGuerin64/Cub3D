/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:51:50 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/17 17:48:25 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	create_monsters(t_app *app)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = 0;
	while (y < app->map_height)
	{
		x = 0;
		while (x < app->map_width)
		{
			if (app->map[y][x] == 'M')
			{
				vector_set(&app->monster[i].position, x + 0.5, y + 0.5);
				app->monster[i].health = MONSTER_HP;
				app->monster[i].is_visible = false;
				i++;
			}
			x++;
		}
		y++;
	}
}

bool	init_monsters(t_app *app)
{
	app->monster = ft_calloc(app->monster_nb + 1, sizeof(*app->monster));
	if (!app->monster)
	{
		perror("ft_calloc");
		return (false);
	}
	create_monsters(app);
	app->raycast.sprite_order = malloc(sizeof(*app->raycast.sprite_order)
			* app->monster_nb);
	if (!app->raycast.sprite_order)
	{
		perror("malloc");
		free(app->monster);
		return (false);
	}
	app->raycast.sprite_distance = malloc(sizeof(*app->raycast.sprite_distance)
			* app->monster_nb);
	if (!app->raycast.sprite_distance)
	{
		perror("malloc");
		free(app->monster);
		free(app->raycast.sprite_order);
		return (false);
	}
	return (true);
}

void	remove_monster(t_app *app, int index)
{
	while (index < app->monster_nb - 1)
	{
		app->monster[index] = app->monster[index + 1];
		index++;
	}
	app->monster_nb--;
}

static bool	monster_to_player(t_app *app, int i)
{
	t_vector	direction;
	double		length;

	vector_set(&direction,
		app->player.position.x - app->monster[i].position.x,
		app->player.position.y - app->monster[i].position.y);
	length = vector_length(&direction);
	if (length < 0.5)
		return (player_hit(app, i));
	vector_set(&direction,
		direction.x / length * MONSTER_SPEED,
		direction.y / length * MONSTER_SPEED);
	if (app->map[(int)(app->monster[i].position.y)]
			[(int)(app->monster[i].position.x + direction.x)] != '1')
		app->monster[i].position.x += direction.x;
	if (app->map[(int)(app->monster[i].position.y + direction.y)]
			[(int)(app->monster[i].position.x)] != '1')
		app->monster[i].position.y += direction.y;
	return (false);
}

void	monsters_follow_player(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->monster_nb)
	{
		if (app->monster[i].is_visible)
		{
			if (!monster_to_player(app, i))
				i++;
		}
		else
			i++;
	}
}

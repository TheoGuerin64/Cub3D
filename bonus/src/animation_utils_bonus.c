/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <ltruchel@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:39:47 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/17 12:43:44 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int	direction_to_wall(t_app *app, t_vector spawn)
{
	int	left_from_player;

	if (app->map[(int)spawn.y][(int)spawn.x] == 'N')
		left_from_player = 1;
	else if (app->map[(int)spawn.y][(int)spawn.x] == 'E')
		left_from_player = 2;
	else if (app->map[(int)spawn.y][(int)spawn.x] == 'S')
		left_from_player = 3;
	if (app->map[(int)spawn.y][(int)spawn.x] == 'W')
		left_from_player = 4;
	return (left_from_player);
}

static void	move_to_wall(int left_from_player, t_ivector *anim_pos)
{
	if (left_from_player == 1)
		anim_pos->x -= 1;
	else if (left_from_player == 2)
		anim_pos->y -= 1;
	else if (left_from_player == 3)
		anim_pos->x += 1;
	else
		anim_pos->y += 1;
}

void	choose_anim_pos(t_app *app)
{
	int			left_from_player;
	t_ivector	anim_pos;

	ivector_set(&anim_pos, app->player.position.x, app->player.position.y);
	left_from_player = direction_to_wall(app, app->player.position);
	while (app->map[anim_pos.y][anim_pos.x] != '1')
		move_to_wall(left_from_player, &anim_pos);
	ivector_set(&app->anim.pos, anim_pos.x, anim_pos.y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:09:46 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/18 15:53:02 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	monster_hit(t_app *app, int index)
{
	app->monster[index].health--;
	if (app->monster[index].health == 0)
	{
		if (app->monster_nb > 1)
			system("paplay ./bonus/assets/mob_death.ogg &");
		else
			system("paplay "EXIT_OPEN_SFX" &");
		remove_monster(app, index);
	}
}

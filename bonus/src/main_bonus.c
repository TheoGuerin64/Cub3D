/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:19:41 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/20 16:01:35 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	free_all(t_app *app)
{
	delete_gun_xpm(app, GUN_NB_FRAME);
	mlx_terminate(app->mlx);
	ft_split_free(app->map);
	ft_free_texture(app->texture);
	free_monsters(app);
	free(app->anim.frame);
	free(app->door);
}

static bool	init(t_app *app)
{
	ivector_set(&app->raycast.half_screen, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	init_player(app);
	choose_anim_pos(app);
	if (!define_door(app))
	{
		ft_fprintf(2, "Error: Failed to init doors\n");
		ft_split_free(app->map);
		ft_free_texture(app->texture);
		return (false);
	}
	if (!init_monsters(app))
	{
		ft_fprintf(2, "Error: Failed to init monsters\n");
		ft_split_free(app->map);
		ft_free_texture(app->texture);
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
	{
		ft_fprintf(2, "Use correct format\nCorrect format is: ./cub3D_bonus"
			" file\n");
		return (EXIT_FAILURE);
	}
	scene_parsing(argv[1], &app);
	if (!init(&app))
		return (EXIT_FAILURE);
	if (!create_window(&app))
	{
		free(app.door);
		free_monsters(&app);
		ft_split_free(app.map);
		ft_free_texture(app.texture);
		return (EXIT_FAILURE);
	}
	minimap(&app);
	mlx_loop(app.mlx);
	free_all(&app);
	return (EXIT_SUCCESS);
}

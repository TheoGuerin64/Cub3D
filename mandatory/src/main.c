/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:19:41 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/01 22:31:39 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	free_all(t_app *app)
{
	int	i;

	mlx_delete_image(app->mlx, app->image);
	i = 0;
	while (i < NB_TEXTURE)
	{
		mlx_delete_xpm42(app->texture[i].ptr);
		i++;
	}
	mlx_terminate(app->mlx);
	ft_split_free(app->map);
	ft_free_texture(app->texture);
}

int	main(int argc, char *argv[])
{
	t_app	app;

	if (argc != 2)
	{
		ft_fprintf(2, "Use correct format\nCorrect format is: ./cub3D file\n");
		return (EXIT_FAILURE);
	}
	scene_parsing(argv[1], &app);
	init_player(&app);
	if (!create_window(&app))
	{
		ft_fprintf(2, "Error\nFailed to create window\n");
		return (EXIT_FAILURE);
	}
	mlx_loop(app.mlx);
	free_all(&app);
	return (EXIT_SUCCESS);
}

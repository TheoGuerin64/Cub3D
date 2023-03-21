/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:53:13 by ltruchel          #+#    #+#             */
/*   Updated: 2023/02/17 16:30:15 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
#include "../../includes/parsing.h"
#include <fcntl.h>

static void	check_extension(char *arg);
static int	file_opening(char *file);
static void	get_infos(t_app *app, char **scene,
				char **texture_name, char **texture_file);
static void	free_parsing_exit(char **scene, char **texture_name,
				char **texture_file, int lvl);

void	scene_parsing(char *arg, t_app *app)
{
	int		fd;
	char	**scene;
	char	**texture_name;
	char	**texture_file;

	check_extension(arg);
	fd = file_opening(arg);
	scene = get_scene(fd);
	texture_name = check_texture_name(scene);
	if (!texture_name)
		free_parsing_exit(scene, NULL, NULL, 1);
	texture_file = check_texture_file(scene, texture_name);
	if (!texture_file)
		free_parsing_exit(scene, texture_name, NULL, 2);
	if (!check_map(scene))
		free_parsing_exit(scene, texture_name, texture_file, 3);
	get_infos(app, scene, texture_name, texture_file);
}

static void	check_extension(char *arg)
{
	char	*last_dot;

	last_dot = ft_strrchr(arg, '.');
	if (!last_dot)
	{
		ft_fprintf(2, "File extension is not .cub\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(last_dot, ".cub"))
	{
		ft_fprintf(2, "File extension is not .cub\n");
		exit(EXIT_FAILURE);
	}
}

static void	get_infos(t_app *app, char **scene,
		char **texture_name, char **texture_file)
{
	app->map = get_map(scene);
	set_map_size(app, app->map);
	fill_map_space(app, app->map);
	get_spawn(app->map, app);
	get_texture(app, texture_name, texture_file);
	get_color(app, texture_name, texture_file);
	free_parsing_exit(scene, texture_name, texture_file, 4);
}

static int	file_opening(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "File is not valid\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void	free_parsing_exit(char **scene, char **texture_name,
		char **texture_file, int lvl)
{
	if (lvl == 1)
	{
		ft_split_free(scene);
		exit (EXIT_FAILURE);
	}
	else if (lvl == 2)
	{
		ft_split_free(texture_name);
		ft_split_free(scene);
		exit (EXIT_FAILURE);
	}
	else if (lvl == 3)
	{
		ft_split_free(texture_file);
		ft_split_free(texture_name);
		ft_split_free(scene);
		exit (EXIT_FAILURE);
	}
	else if (lvl == 4)
	{
		ft_split_free(scene);
		ft_split_free(texture_name);
		ft_split_free(texture_file);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <ltruchel@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:15:41 by ltruchel          #+#    #+#             */
/*   Updated: 2023/02/28 15:16:29 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
#include "../../includes/parsing.h"
#include <fcntl.h>

static void	exit_empty_file(char *joined_line, int fd);

char	**get_scene(int fd)
{
	char	*line;
	char	*joined_line;
	char	*tmp;
	char	**scene;

	joined_line = ft_strdup("");
	line = ft_get_next_line(fd);
	if (line == NULL)
		exit_empty_file(joined_line, fd);
	while (line)
	{
		tmp = ft_strdup(joined_line);
		free(joined_line);
		joined_line = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
		line = ft_get_next_line(fd);
	}
	scene = ft_split(joined_line, '\n');
	free (joined_line);
	close (fd);
	if (!scene)
		exit(EXIT_FAILURE);
	return (scene);
}

static void	exit_empty_file(char *joined_line, int fd)
{
	free(joined_line);
	close (fd);
	ft_fprintf(2, "File is empty\n");
	exit(EXIT_FAILURE);
}

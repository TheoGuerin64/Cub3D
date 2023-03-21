/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:58:11 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/16 10:33:37 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include <fcntl.h>

static char	*filltexture_file(char *line)
{
	char	*texture_file;
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return (NULL);
	texture_file = ft_strdup(split[1]);
	if (!texture_file)
		return (NULL);
	ft_split_free(split);
	return (texture_file);
}

char	**get_texture_file(char **scene)
{
	int		i;
	int		j;
	char	**texture_file;

	i = 0;
	j = 0;
	texture_file = ft_calloc(sizeof(char *), NB_TEXTURE + NB_COLOR + 1);
	while (scene[i] && j < NB_TEXTURE + NB_COLOR)
	{
		if (!is_empty(scene[i]))
		{
			texture_file[j] = filltexture_file(scene[i]);
			j++;
		}
		i++;
	}
	return (texture_file);
}

static bool	check_texture_extension(char **texture_file,
		const char *xpm, char **texture_name)
{
	int		i;
	char	*last_dot;

	i = 0;
	while (texture_file[i] && i < NB_TEXTURE)
	{
		if (texture_name[i][0] != 'F' && texture_name[i][0] != 'C')
		{
			last_dot = ft_strrchr(texture_file[i], '.');
			if (!last_dot || ft_strcmp(last_dot, xpm))
			{
				ft_fprintf(2, "Texture files must be in .xpm42 format\n");
				return (false);
			}
		}
		i++;
	}
	return (true);
}

static bool	check_valid_xpm(char **texture_file, char **texture_name)
{
	int	i;
	int	fd;

	i = 0;
	while (i < NB_TEXTURE + NB_COLOR)
	{
		if (texture_name[i][0] != 'F' && texture_name[i][0] != 'C')
		{
			fd = open(texture_file[i], O_RDONLY);
			if (fd == -1)
			{
				ft_fprintf(2, "Couldn't open an .xpm42 file\n");
				return (false);
			}
			close(fd);
		}
		i++;
	}
	return (true);
}

bool	check_valid_rgb(char **texture_file, char **texture_name);

char	**check_texture_file(char **scene, char **texture_name)
{
	char	**texture_file;

	texture_file = get_texture_file(scene);
	if (!check_texture_extension(texture_file, ".xpm42", texture_name))
	{
		ft_split_free(texture_file);
		return (NULL);
	}
	if (!check_valid_xpm(texture_file, texture_name))
	{
		ft_split_free(texture_file);
		return (NULL);
	}
	if (!check_valid_rgb(texture_file, texture_name))
	{
		ft_split_free(texture_file);
		return (NULL);
	}
	return (texture_file);
}

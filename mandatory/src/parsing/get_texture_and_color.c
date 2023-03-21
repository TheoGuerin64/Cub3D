/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_and_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:01:06 by ltruchel          #+#    #+#             */
/*   Updated: 2023/02/28 15:39:23 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	sort_texture(char **texture_name, char **texture_file);

void	get_texture(t_app *app, char **texture_name, char **texture_file)
{
	int	i;
	int	j;

	sort_texture(texture_name, texture_file);
	i = 0;
	j = 0;
	while (i < NB_TEXTURE + NB_COLOR)
	{
		if (texture_name[i][0] != 'F' && texture_name[i][0] != 'C')
		{
			app->texture[j].path = ft_strdup(texture_file[i]);
			if (!app->texture[j].path)
				return ;
			j++;
		}
		i++;
	}
}

void	get_color(t_app *app, char **texture_name, char **texture_file)
{
	int		i;
	char	**split_rgb;

	i = -1;
	while (++i < NB_TEXTURE + NB_COLOR)
	{
		if (texture_name[i][0] == 'F')
		{
			split_rgb = ft_split(texture_file[i], ',');
			if (!split_rgb)
				return ;
			app->floor_color = rgb(ft_atoi(split_rgb[0], NULL),
					ft_atoi(split_rgb[1], NULL), ft_atoi(split_rgb[2], NULL));
			ft_split_free(split_rgb);
		}
		if (texture_name[i][0] == 'C')
		{
			split_rgb = ft_split(texture_file[i], ',');
			if (!split_rgb)
				return ;
			app->ceiling_color = rgb(ft_atoi(split_rgb[0], NULL),
					ft_atoi(split_rgb[1], NULL), ft_atoi(split_rgb[2], NULL));
			ft_split_free(split_rgb);
		}
	}
}

/* Sort texture in ASCII order E N S W                                    */

static void	sort_texture(char **texture_name, char **texture_file)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (i < NB_TEXTURE + NB_COLOR)
	{
		j = 0;
		while (j < NB_TEXTURE + NB_COLOR - 1)
		{
			if (ft_strcmp(texture_name[j], texture_name[j + 1]) > 0)
			{
				tmp = texture_name[j];
				tmp2 = texture_file[j];
				texture_name[j] = texture_name[j + 1];
				texture_file[j] = texture_file[j + 1];
				texture_name[j + 1] = tmp;
				texture_file[j + 1] = tmp2;
			}
			j++;
		}
		i++;
	}
}

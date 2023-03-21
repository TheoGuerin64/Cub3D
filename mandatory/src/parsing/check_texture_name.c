/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:11:33 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/21 15:21:10 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
#include "../../includes/parsing.h"

static bool	check_line_nb_split(char **scene);
static char	**get_header_texture(char **scene, int *nb_found);
static bool	check_texture_found(char **found_texture_name);

char	**check_texture_name(char **scene)
{
	char		**found_texture_name;
	static int	nb_found = 0;

	if (!check_line_nb_split(scene))
		return (NULL);
	found_texture_name = get_header_texture(scene, &nb_found);
	if (nb_found < NB_TEXTURE + NB_COLOR)
	{
		ft_split_free(found_texture_name);
		return (NULL);
	}
	if (!check_texture_found(found_texture_name))
	{
		ft_split_free(found_texture_name);
		return (NULL);
	}
	return (found_texture_name);
}

static bool	check_line_nb_split(char **scene)
{
	int		i;
	char	**split;

	i = 0;
	while (scene[i] && i < NB_TEXTURE + NB_COLOR)
	{
		split = ft_split(scene[i], ' ');
		if (ft_split_size(split) != 2)
		{
			ft_split_free(split);
			ft_fprintf(2, "Invalid scene\n");
			return (false);
		}
		ft_split_free(split);
		i++;
	}
	return (true);
}

static char	*fill_texture_found_array(char *line);

char	**get_header_texture(char **scene, int *nb_found)
{
	int		i;
	char	**found_texture_name;

	i = 0;
	found_texture_name = ft_calloc(sizeof(char *), NB_TEXTURE + NB_COLOR + 1);
	if (!found_texture_name)
		return (NULL);
	while (scene[i])
	{
		if (!is_empty(scene[i]))
		{
			found_texture_name[*nb_found]
				= fill_texture_found_array(scene[i]);
			*nb_found += 1;
			if (*nb_found == NB_TEXTURE + NB_COLOR)
				break ;
		}
		i++;
	}
	return (found_texture_name);
}

static char	*fill_texture_found_array(char *line)
{
	char	*found_texture_name;
	char	**split;

	split = ft_split(line, ' ');
	if (!split)
		return (NULL);
	found_texture_name = ft_strdup(split[0]);
	if (!found_texture_name)
		return (NULL);
	ft_split_free(split);
	return (found_texture_name);
}

void		define_v_texture(char **v_texture);

static bool	check_texture_found(char **found_texture_name)
{
	int		i;
	int		j;
	int		cnt_v_f_texture;
	char	*v_texture[NB_TEXTURE + NB_COLOR];

	i = 0;
	cnt_v_f_texture = 0;
	define_v_texture(v_texture);
	while (i < NB_TEXTURE + NB_COLOR)
	{
		j = 0;
		while (j < NB_TEXTURE + NB_COLOR)
		{
			if (!ft_strcmp_null(found_texture_name[j], v_texture[i]))
			{
				v_texture[i] = 0;
				cnt_v_f_texture += 1;
			}
			j++;
		}
		i++;
	}
	if (cnt_v_f_texture != NB_TEXTURE + NB_COLOR)
		return (false);
	return (true);
}

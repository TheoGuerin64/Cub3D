/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb_color_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <ltruchel@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:35:53 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/17 12:43:45 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"
#include "../../includes/parsing_bonus.h"

bool	check_floor_ceiling(char *texture_file)
{
	int		rgb_cnt;
	int		color;
	char	**rgb_split;

	rgb_split = ft_split(texture_file, ',');
	if (ft_split_size(rgb_split) != 3)
	{
		ft_fprintf(2, "Color must be in RGB format\n");
		ft_split_free(rgb_split);
		return (false);
	}
	rgb_cnt = 0;
	while (rgb_cnt < 3)
	{
		color = ft_atoi(rgb_split[rgb_cnt], NULL);
		if (color < 0 || color > 255 || !is_only_digits(rgb_split[rgb_cnt]))
		{
			ft_fprintf(2, "RGB color must be in range [0,255]\n");
			ft_split_free(rgb_split);
			return (false);
		}
		rgb_cnt++;
	}
	ft_split_free(rgb_split);
	return (true);
}

bool	check_valid_rgb(char **texture_file, char **texture_name)
{
	int		i;

	i = 0;
	while (i < NB_TEXTURE + NB_COLOR)
	{
		if (texture_name[i][0] == 'F' || texture_name[i][0] == 'C')
		{
			if (!check_floor_ceiling(texture_file[i])
				|| ft_strcount(texture_file[i], ',') != 2)
				return (false);
		}
		i++;
	}
	return (true);
}

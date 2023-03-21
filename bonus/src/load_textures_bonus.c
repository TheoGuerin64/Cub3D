/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 17:28:14 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/20 16:05:23 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

bool	xpm42_to_array(int pixels[256][256], char *path)
{
	xpm_t	*texture;
	int		i;

	texture = mlx_load_xpm42(path);
	if (!texture || (texture->texture.width != TEXTURE_SIZE
			|| texture->texture.height != TEXTURE_SIZE))
	{
		if (texture)
			mlx_delete_xpm42(texture);
		ft_fprintf(2, "Error: Failed to load texture %s\n", path);
		return (false);
	}
	i = 0;
	while (i < TEXTURE_SIZE * TEXTURE_SIZE)
	{
		pixels[i / TEXTURE_SIZE][i % TEXTURE_SIZE] = (
				texture->texture.pixels[i * 4 + 3]
				| texture->texture.pixels[i * 4 + 2] << 8
				| texture->texture.pixels[i * 4 + 1] << 16
				| texture->texture.pixels[i * 4 + 0] << 24);
		i++;
	}
	mlx_delete_xpm42(texture);
	return (true);
}

static bool	load_wall_textures(t_app *app)
{
	int	i;

	i = 0;
	while (i < NB_TEXTURE)
	{
		if (!xpm42_to_array(app->texture[i].pixels, app->texture[i].path))
		{
			ft_putstr_fd("Error: Failed to load wall textures\n", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	load_animation_xpm(t_app *app)
{
	int		i;
	char	path[44];
	char	nb[3];

	app->anim.frame = malloc(sizeof(*app->anim.frame) * NB_FRAME);
	if (!app->anim.frame)
		return (false);
	ft_strlcpy(path, ANIM_FRAME_PATH, 36);
	nb[2] = '\0';
	i = 0;
	while (i < NB_FRAME)
	{
		nb[0] = i / 10 + '0';
		nb[1] = i % 10 + '0';
		ft_strlcpy(path + 35, nb, 3);
		ft_strlcat(path + 35, ".xpm42", 10);
		if (!xpm42_to_array(app->anim.frame[i].pixels, path))
		{
			free(app->anim.frame);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	load_gun_xpm(t_app *app)
{
	int		i;
	char	path[31];
	char	nb[2];

	ft_strlcpy(path, GUN_FRAME_PATH, 24);
	nb[1] = '\0';
	i = 0;
	while (i < GUN_NB_FRAME)
	{
		nb[0] = i % 10 + '0';
		ft_strlcpy(path + 23, nb, 2);
		ft_strlcat(path + 21, ".xpm42", 10);
		app->gun_texture[i] = mlx_load_xpm42(path);
		if (!app->gun_texture[i])
		{
			delete_gun_xpm(app, i);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	load_textures(t_app *app)
{
	if (!load_wall_textures(app))
		return (false);
	if (!xpm42_to_array(app->floor_ceiling_texture[0].pixels, FLOOR_PATH))
		return (false);
	if (!xpm42_to_array(app->floor_ceiling_texture[1].pixels, CEILING_PATH))
		return (false);
	if (!xpm42_to_array(app->monster_texture.pixels, MONSTER_PATH))
		return (false);
	if (!xpm42_to_array(app->door_full.pixels, DOORCLOSED_PATH)
		|| !xpm42_to_array_door(app->door_part[0].pixels, DOORRIGHT_PATH)
		|| !xpm42_to_array_door(app->door_part[1].pixels, DOORLEFT_PATH))
		return (false);
	if (!load_exit_texture(app))
		return (false);
	if (!load_animation_xpm(app))
		return (false);
	if (!load_gun_xpm(app))
	{
		free(app->anim.frame);
		return (false);
	}
	return (true);
}

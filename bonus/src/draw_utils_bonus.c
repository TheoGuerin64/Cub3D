/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:24:14 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/17 16:05:34 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	texture_index(t_raycast *raycast)
{
	if (raycast->side == 0)
	{
		if (raycast->ray_dir.x > 0)
			return (0);
		else
			return (3);
	}
	else
	{
		if (raycast->ray_dir.y > 0)
			return (2);
		else
			return (1);
	}
}

bool	draw_texture(mlx_image_t *image, mlx_texture_t *texture,
	uint32_t x, uint32_t y)
{
	uint8_t		*pixelx;
	uint8_t		*pixeli;
	uint32_t	i;

	i = 0;
	while (i < texture->height)
	{
		pixelx = &texture->pixels[(i * texture->width)
			* texture->bytes_per_pixel];
		pixeli = &image->pixels[((i + y) * image->width + x)
			* texture->bytes_per_pixel];
		ft_memmove(pixeli, pixelx, texture->width * texture->bytes_per_pixel);
		i++;
	}
	return (true);
}

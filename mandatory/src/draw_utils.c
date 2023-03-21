/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:24:14 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/02 13:40:01 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	rgb(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

int	rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	texture_pixel_at(mlx_texture_t *texture, int x, int y)
{
	return (0xFF
		| texture->pixels[(y * texture->width + x) * 4 + 2] << 8
		| texture->pixels[(y * texture->width + x) * 4 + 1] << 16
		| texture->pixels[(y * texture->width + x) * 4 + 0] << 24);
}

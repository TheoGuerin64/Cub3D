/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:15:25 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/20 14:30:59 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	rgb(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

int	rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

unsigned char	alpha(int color)
{
	return (color & 0x000000FF);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:23:00 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/17 12:43:45 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	vector_rotate(t_matrix *rotation, t_vector *vector)
{
	double	vector_x;

	vector_x = vector->x;
	vector->x = vector_x * rotation->a + vector->y * rotation->b;
	vector->y = vector_x * rotation->c + vector->y * rotation->d;
}

void	vector_set(t_vector *vector, double x, double y)
{
	vector->x = x;
	vector->y = y;
}

void	ivector_set(t_ivector *vector, int x, int y)
{
	vector->x = x;
	vector->y = y;
}

double	vector_length(t_vector *vector)
{
	return (sqrt(vector->x * vector->x + vector->y * vector->y));
}

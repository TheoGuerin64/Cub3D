/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:13:21 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/17 12:41:18 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_BONUS_H
# define VECTOR_BONUS_H

typedef struct s_vector
{
	double	x;
	double	y;
}		t_vector;

typedef struct s_ivector
{
	int	x;
	int	y;
}		t_ivector;

typedef struct s_matrix
{
	double	a;
	double	b;
	double	c;
	double	d;
}		t_matrix;

void	vector_rotate(t_matrix *rotation, t_vector *vector);
void	vector_set(t_vector *vector, double x, double y);
void	ivector_set(t_ivector *vector, int x, int y);
double	vector_length(t_vector *vector);

#endif

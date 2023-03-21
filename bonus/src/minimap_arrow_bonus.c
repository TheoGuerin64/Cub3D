/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_arrow_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <ltruchel@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:04:41 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/17 12:43:45 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int	define_s(double p1, double p2)
{
	if (p1 < p2)
		return (1);
	else
		return (-1);
}

static void	move_to_p2(int *error, int delta, double *p1, int slope)
{
	*error += delta;
	*p1 += slope;
}

static void	draw_line(t_app *app, t_vector p1, t_vector p2, int color)
{
	int			deltax;
	int			deltay;
	int			error;
	int			error2;
	t_ivector	s;

	vector_set(&p1, floor(p1.x), floor(p1.y));
	vector_set(&p2, floor(p2.x), floor(p2.y));
	deltax = ft_abs(p2.x - p1.x);
	deltay = -ft_abs(p2.y - p1.y);
	error = deltax + deltay;
	s.x = define_s(p1.x, p2.x);
	s.y = define_s(p1.y, p2.y);
	while (1)
	{
		mlx_put_pixel(app->image_hud, p1.x + MINIMAP_X,
			p1.y + MINIMAP_Y, color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		error2 = error * 2;
		if (error2 >= deltay)
			move_to_p2(&error, deltay, &p1.x, s.x);
		if (error2 <= deltax)
			move_to_p2(&error, deltax, &p1.y, s.y);
	}
}

static void	draw_multiple_lines(t_app *app, t_vector *tmp, t_vector *a)
{
	int			arrow_width;
	t_vector	b;
	t_vector	c;

	arrow_width = ARROW_WIDTH;
	while (arrow_width != 0)
	{
		b.x = tmp->x + arrow_width * app->player.direction.y;
		b.y = tmp->y - arrow_width * app->player.direction.x;
		c.x = tmp->x - arrow_width * app->player.direction.y;
		c.y = tmp->y + arrow_width * app->player.direction.x;
		draw_line(app, *a, b, C_ARR);
		draw_line(app, *a, c, C_ARR);
		draw_line(app, b, c, C_ARR);
		arrow_width--;
	}
}

void	draw_arrow(t_app *app)
{
	t_vector	tmp;
	t_vector	a;
	int			arrow_height;

	tmp.x = (float)MINIMAP_WIDTH / 2;
	tmp.y = (float)MINIMAP_HEIGHT / 2;
	arrow_height = ARROW_HEIGHT;
	while (arrow_height != 0)
	{
		a.x = (float)MINIMAP_WIDTH / 2 + arrow_height * app->player.direction.x;
		a.y = (float)MINIMAP_HEIGHT / 2 + arrow_height
			* app->player.direction.y;
		draw_multiple_lines(app, &tmp, &a);
		arrow_height--;
	}
}

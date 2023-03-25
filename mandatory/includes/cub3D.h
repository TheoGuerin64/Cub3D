/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:19:06 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/25 14:16:17 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# include "../../libft/libft.h"
# include "../../MLX42/include/MLX42/MLX42.h"
# include "../../MLX42/include/MLX42/MLX42_Input.h"

# define WIN_TITLE "cub3D"
# define WIN_WIDTH 1920
# define WIN_HEIGHT 995

# define ROTATION_SPEED 0.10471975511965977
# define SPEED 0.071
# define FOV 60

# define NB_TEXTURE 4
# define NB_COLOR 2
# define TEXTURE_SIZE 256

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

typedef struct s_player
{
	t_vector	position;
	t_vector	direction;
	t_vector	plane;
}		t_player;

typedef struct s_raycast
{
	t_vector	ray_dir;
	t_vector	delta_dist;
	t_vector	side_dist;
	t_ivector	map_pos;
	t_ivector	step;
	double		camera_x;
	double		wall_dist;
	bool		hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		y_step;
	double		wall_x;
	t_ivector	texture;
	double		texture_pos;
}		t_raycast;

typedef struct s_texture
{
	xpm_t			*ptr;
	char			*path;
}		t_texture;

typedef struct s_app
{
	void		*mlx;
	t_player	player;
	t_raycast	raycast;
	char		**map;
	int			map_width;
	int			map_height;
	t_texture	texture[4];
	int			ceiling_color;
	int			floor_color;
	mlx_image_t	*image;
}		t_app;

// Window
bool	create_window(t_app *app);

// Raycasting
void	raycasting(t_app *app);
void	draw_raycast(t_app *app, int x);

// Draw
void	draw(t_app *app);
int		texture_pixel_at(mlx_texture_t *texture, int x, int y);
int		rgb(int r, int g, int b);
int		rgba(int r, int g, int b, int a);

// Player
void	init_player(t_app *app);
void	rotate_player(t_app *app, int direction);
void	move_player(t_app *app, int dx, int dy);

// Vectors
void	vector_rotate(t_matrix *rotation, t_vector *vector);
void	vector_set(t_vector *vector, double x, double y);
void	ivector_set(t_ivector *vector, int x, int y);

// Parsing
void	scene_parsing(char *arg, t_app *app);

// Utils
bool	is_in_map(t_app *app, int x, int y);
bool	is_valid_pos(t_app *app, int x, int y);
int		texture_index(t_raycast *raycast);
void	ft_free_texture(t_texture texture[NB_TEXTURE]);

#endif

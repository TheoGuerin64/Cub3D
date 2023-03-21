/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:19:06 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/20 15:56:43 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# include "../../libft/libft.h"
# include "../../MLX42/include/MLX42/MLX42.h"
# include "../../MLX42/include/MLX42/MLX42_Input.h"

# include "const_bonus.h"
# include "vector_bonus.h"
# include "color_bonus.h"

typedef struct s_player
{
	int			hp;
	double		last_shoot;
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
	t_vector	floor_wall;
	t_vector	current_floor;
	t_ivector	floor_texture;
	double		weight;
	t_ivector	half_screen;
	double		z_buffer[WIN_WIDTH];
	int			*sprite_order;
	double		*sprite_distance;
	t_vector	transform;
	t_vector	sprite;
	t_ivector	sprite_size;
	double		inv_det;
	int			sprite_screen_x;
	int			stripe;
	int			v_move_screen;
}		t_raycast;

typedef struct s_texture
{
	char	*path;
	int		pixels[TEXTURE_SIZE][TEXTURE_SIZE];
}		t_texture;

typedef struct s_texture_d
{
	char	*path;
	int		pixels[TEXTURE_SIZE][DOOR_TEXTURE_WIDTH];
}		t_texture_d;

typedef struct s_door
{
	int			index;
	int			texture_shift;
	int			state;
	int			door_action;
	int			door_raycast_begin;
	int			door_raycast_end;
	bool		door_raycast_bool;
	double		time;
	t_ivector	pos;
}	t_door;

typedef struct s_animation
{
	t_ivector	pos;
	t_texture	*frame;
}		t_animation;

typedef struct s_minimap
{
	int			arrow_width;
	int			arrow_height;
	t_ivector	map_start;
	t_ivector	map_end;
	t_ivector	map_pos;
	t_vector	p_player;
	t_vector	p_aheadplayer;
	t_vector	p_lplayer;
	t_vector	p_rplayer;
}	t_minimap;

typedef struct s_monster
{
	t_vector	position;
	int			health;
	bool		is_visible;
	double		transform_x;
}		t_monster;

typedef struct s_exit
{
	t_ivector	pos;
}		t_exit;

typedef struct s_app
{
	mlx_t		*mlx;
	t_player	player;
	t_raycast	raycast;
	char		**map;
	int			map_width;
	int			map_height;
	t_texture	texture[4];
	t_texture	floor_ceiling_texture[2];
	t_texture	door_full;
	t_texture	exit_texture[NB_EXIT_TEXTURE];
	t_texture_d	door_part[2];
	t_texture	monster_texture;
	xpm_t		*gun_texture[GUN_NB_FRAME];
	int			ceiling_color;
	int			floor_color;
	mlx_image_t	*image;
	mlx_image_t	*image_hud;
	t_animation	anim;
	t_minimap	minimap;
	t_monster	*monster;
	int			monster_nb;
	int			nb_door;
	int			door_to_draw;
	bool		lose;
	bool		win;
	t_door		*door;
	t_exit		exit;
	xpm_t		*icon;
}		t_app;

typedef enum e_doorpart {
	DOOR_RIGHT,
	DOOR_LEFT
}	t_doorpart;

typedef enum e_dooraction {
	OPENING,
	CLOSING,
	OPEN,
	CLOSED
}	t_dooraction;

void	calcul_monster_pos(t_app *app, int i);
void	calcul_pos(t_app *app);
int		calcul_texture_x(t_app *app);
void	change_tile_door(t_app *app, char c);
void	choose_anim_pos(t_app *app);
bool	create_window(t_app *app);
bool	define_door(t_app *app);
bool	define_exit_pos(t_app *app);
void	delete_gun_xpm(t_app *app, int until);
void	draw_animation(t_app *app, int frame_index, int x);
void	draw_arrow(t_app *app);
bool	draw_crosshair(t_app *app);
void	draw_exit(t_app *app, int frame_index, int x);
void	draw_gun(t_app *app, int frame);
void	draw_hp_bar(t_app *app);
void	draw_raycast(t_app *app, int x, t_ivector *door_pos);
int		find_door_index(t_app *app);
void	find_width_door(t_app *app, int x, t_ivector *door_pos);
void	floor_ceiling_casting(t_app *app, int x);
int		frame_index_anim(void);
int		frame_index_exit(void);
void	free_monsters(t_app *app);
void	ft_free_texture(t_texture texture[NB_TEXTURE]);
bool	init_monsters(t_app *app);
void	init_player(t_app *app);
bool	is_door(t_app *app);
bool	is_in_map(t_app *app, int x, int y);
bool	is_sprite_visible(t_app *app);
bool	is_valid_pos(t_app *app, int x, int y, char *set);
void	launch_door_raycast(t_app *app, int x);
bool	load_exit_texture(t_app *app);
bool	load_textures(t_app *app);
void	middle_raycast(t_app *app, char *to_hit);
void	minimap(t_app *app);
void	monster_hit(t_app *app, int index);
void	monsters_follow_player(t_app *app);
void	move_player(t_app *app, int dx, int dy);
void	open_door(t_app *app);
bool	player_hit(t_app *app, int monster_index);
void	raycasting(t_app *app);
void	remove_monster(t_app *app, int index);
void	rotate_player(t_app *app, double angle);
void	scene_parsing(char *arg, t_app *app);
void	select_door_animation(t_app *app, int x, t_door *door);
void	set_door_default(t_app *app);
void	set_shift_all_doors(t_app *app);
void	shoot(t_app *app);
void	show_end_screen(t_app *app, char *outcome_path);
void	sprite_casting(t_app *app);
int		texture_index(t_raycast *raycast);
void	update_gun(t_app *app);
bool	xpm42_to_array(int pixels[256][256], char *path);
bool	xpm42_to_array_door(int pixels[256][514], char *path);
bool	draw_texture(mlx_image_t *image, mlx_texture_t *texture,
			uint32_t x, uint32_t y);
void	win_condition(t_app *app);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:09:47 by ltruchel          #+#    #+#             */
/*   Updated: 2023/03/17 14:45:33 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# include "cub3D_bonus.h"

char		**check_texture_name(char **scene);
char		**check_texture_file(char **scene, char **texture_name);
bool		check_map(char **scene);
bool		check_closed_map(char **map);
char		**get_map(char **scene);
char		**get_scene(int fd);
void		set_map_size(t_app *app, char **map);
void		fill_map_space(t_app *app, char **map);
void		get_spawn_door(char **map, t_app *app);
void		get_texture(t_app *app, char **texture_name, char **texture_file);
void		get_color(t_app *app, char **texture_name, char **texture_file);
void		get_misc(t_app *app, char **map);

/* Utils                                                                      */
bool		is_empty(char *line);
int			ft_strcmp_null(const char *s1, const char *s2);
bool		is_only_digits(char	*str);

#endif

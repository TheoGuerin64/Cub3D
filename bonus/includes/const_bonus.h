/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 18:03:12 by tguerin           #+#    #+#             */
/*   Updated: 2023/03/20 15:09:25 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_BONUS_H
# define CONST_BONUS_H

# define WIN_TITLE "cub3D_Bonus"
# define WIN_WIDTH 1920
# define WIN_HEIGHT 995

# define ROTATION_SPEED 0.10471975511965977
# define MOVE_SPEED 0.071
# define FOV 60

# define NB_TEXTURE 4
# define NB_COLOR 2
# define TEXTURE_SIZE 256

# define LOSE_PATH "./bonus/assets/lose_screen.xpm42"
# define WIN_PATH "./bonus/assets/win_screen.xpm42"

# define FLOOR_PATH "./bonus/assets/floor.xpm42"
# define CEILING_PATH "./bonus/assets/ceiling.xpm42"

# define DOORCLOSED_PATH "./bonus/assets/door_closed.xpm42"
# define DOORRIGHT_PATH "./bonus/assets/door_openleft.xpm42"
# define DOORLEFT_PATH "./bonus/assets/door_openright.xpm42"
# define DOOR_SFX "./bonus/assets/door_sfx.ogg"
# define DOOR_TEXTURE_WIDTH 514
# define DOOR_FRAME_TIME 0.02
# define DOOR_OPENING_DIST 1.0
# define BEGIN 0
# define END 1

# define EXIT_TEXTURE_PATH "./bonus/assets/exit_"
# define NB_EXIT_TEXTURE 9
# define EXIT_FRAME_DURATION 0.035
# define EXIT_RANGE 0.6
# define EXIT_OPEN_SFX "./bonus/assets/exit_open.ogg"

# define MINIMAP_X 25
# define MINIMAP_Y 25
# define MINIMAP_WIDTH 441
# define MINIMAP_HEIGHT 231
# define SQUARE_LEN 21
# define ARROW_HEIGHT 16
# define ARROW_WIDTH 5
# define C_ARR 0xEAFF05FF
# define C_OPEN 0x2B786BAA
# define C_WALL 0x59E3BEAA
# define C_CLOSED_DOOR 0xFF0000FF
# define C_OPEN_DOOR 0x00CC00FF
# define C_EXIT 0x0000FFFF
# define NB_FRAME 56
# define ANIM_FRAME_PATH "./bonus/assets/animation/animation_"

# define MONSTER_PATH "./bonus/assets/monster.xpm42"
# define UDIV 2
# define VDIV 2
# define VMOVE 0.0
# define MONSTER_SPEED 0.05
# define MONSTER_HP 2

# define SENSITIVITY 0.01
# define CROSSHAIR_PATH "./bonus/assets/crosshair.xpm42"
# define CROSSHAIR_SIZE 38

# define SHOOT_WAIT 0.2
# define GUNSHOT_PATH "./bonus/assets/gunshot.ogg"
# define GUN_FRAME_PATH "./bonus/assets/gun/gun_"
# define GUN_NB_FRAME 6
# define GUN_OFFSET 100
# define GUN_FRAME_TIME 0.04

# define BASE_HP 11
# define HP_BAR_X 0
# define HP_BAR_Y 930
# define HP_BAR_WIDTH 400
# define HP_BAR_HEIGHT 32
# define HP_BAR_OFFSET 3
# define C_HP_BAR_BG 0x59E3BEAA
# define C_HP_CURRENT 0xE60F00FF

#endif

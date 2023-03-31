MAKEFLAGS += -j

SRCS :=	main.c \
					window.c \
					raycasting.c \
					vector.c \
					utils.c \
					draw.c \
					draw_utils.c \
					player.c \
					parsing/main_parsing.c \
					parsing/parsing_utils.c \
					parsing/check_texture_name.c \
					parsing/check_texture_file.c \
					parsing/check_rgb_color.c \
					parsing/check_map.c \
					parsing/check_closed_map.c \
					parsing/get_map.c \
					parsing/get_map_bis.c \
					parsing/get_scene.c \
					parsing/get_texture_and_color.c
SRCS:= $(addprefix mandatory/src/, $(SRCS))
SRCS_B	:=	main_bonus.c \
				window_bonus.c \
				raycasting_bonus.c \
				vector_bonus.c \
				utils_bonus.c \
				draw_bonus.c \
				draw_utils_bonus.c \
				player_bonus.c \
				floor_ceiling_casting_bonus.c \
				load_textures_bonus.c \
				animation_bonus.c \
				animation_utils_bonus.c \
				minimap_bonus.c \
				minimap_arrow_bonus.c \
				monster_bonus.c \
				monster2_bonus.c \
				color_bonus.c \
				hud_bonus.c \
				hp_bar_bonus.c \
				sprite_casting_bonus.c \
				sprite_casting2_bonus.c \
				door_draw_bonus.c \
				door_utils_bonus.c \
				door_raycast_bonus.c \
				door_open_bonus.c \
				win_bonus.c \
				parsing/main_parsing_bonus.c \
				parsing/parsing_utils_bonus.c \
				parsing/check_texture_name_bonus.c \
				parsing/check_texture_file_bonus.c \
				parsing/check_rgb_color_bonus.c \
				parsing/check_map_bonus.c \
				parsing/check_closed_map_bonus.c \
				parsing/get_map_bonus.c \
				parsing/get_map_bis_bonus.c \
				parsing/get_scene_bonus.c \
				parsing/get_texture_and_color_bonus.c
SRCS_B := $(addprefix bonus/src/, $(SRCS_B))

FT_SRC :=	./libft
MLX_SRC :=	./MLX42

OBJS :=		${SRCS:.c=.o}
OBJS_B :=		${SRCS_B:.c=.o}
NAME :=		cub3D
NAME_B :=		cub3D_bonus
CC :=		clang
CFLAGS :=	-Wall -Wextra -Werror -Ofast ${DEBUG}
LIBS :=		-lft -L${FT_SRC} ${MLX_SRC}/build/libmlx42.a -ldl -lglfw -pthread -lm

.c.o:
			@${CC} -c ${CFLAGS} $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${MLX_SRC}/build/libmlx42.a
			@make -sC ${FT_SRC}
			@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}
			@printf "\033[0;31mCompiled\033[0m\n"

${NAME_B}:	${OBJS_B} ${MLX_SRC}/build/libmlx42.a
			@make -sC ${FT_SRC}
			@${CC} ${CFLAGS} -o ${NAME_B} ${OBJS_B} ${LIBS}
			@printf "\033[0;31mCompiled\033[0m\n"

${MLX_SRC}/build/libmlx42.a:
			@cmake ${MLX_SRC} -B ${MLX_SRC}/build && make -sC ${MLX_SRC}/build -j4

clean:
			@make -sC ${FT_SRC} clean
			@${RM} ${OBJS} ${OBJS_B}
			@printf "\033[0;31mCleaned\033[0m\n"

fclean:
			@make -sC ${FT_SRC} fclean
			@${RM} ${OBJS} ${OBJS_B} ${NAME} ${NAME_B}
			@printf "\033[0;31mCleaned\033[0m\n"

re:			fclean
			@${MAKE} -s all

all:		${NAME}

bonus:		${NAME_B}

.PHONY: all, clean, fclean, re, bonus


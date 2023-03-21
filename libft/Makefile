MAKEFLAGS += -sj

SRCS =	char/ft_isalpha.c \
		char/ft_isalnum.c \
		char/ft_isalpha.c \
		char/ft_isdigit.c \
		char/ft_isascii.c \
		char/ft_isprint.c \
		char/ft_toupper.c \
		char/ft_tolower.c \
		ft_fprintf/ft_fprintf.c \
		ft_fprintf/ft_fprintf_utils.c \
		ft_fprintf/ft_fprintf_utils2.c \
		get_next_line/get_next_line.c \
		math/ft_abs.c \
		math/ft_dabs.c \
		memory/ft_memchr.c \
		memory/ft_memcmp.c \
		memory/ft_memset.c \
		memory/ft_bzero.c \
		memory/ft_memcpy.c \
		memory/ft_memmove.c \
		memory/ft_calloc.c \
		put/ft_putchar_fd.c \
		put/ft_putstr_fd.c \
		put/ft_putnbr_fd.c \
		put/ft_putendl_fd.c \
		string/ft_strlen.c \
		string/ft_strlcpy.c \
		string/ft_strchr.c \
		string/ft_strrchr.c \
		string/ft_strnstr.c \
		string/ft_atoi.c \
		string/ft_atol.c \
		string/ft_strlcat.c \
		string/ft_strcat.c \
		string/ft_strcmp.c \
		string/ft_strncmp.c \
		string/ft_strdup.c \
		string/ft_substr.c \
		string/ft_strjoin.c \
		string/ft_strtrim.c \
		string/ft_itoa.c \
		string/ft_strmapi.c \
		string/ft_striteri.c \
		string/ft_strrem.c \
		string/ft_strcount.c \
		split/ft_split.c \
		split/ft_split_dup.c \
		split/ft_split_free.c \
		split/ft_split_join.c \
		split/ft_split_remove.c \
		split/ft_split_sort.c \
		split/ft_split_len.c \
		split/ft_split_size.c \
		split/ft_split_append.c \
		split/ft_split_slice.c \
		split/ft_split_count.c \
		split/ft_split_print.c

OBJS	= ${SRCS:.c=.o}
NAME	:= libft.a
CC		:= clang
CFLAGS	:= -Wall -Wextra -Werror -g3 -fPIC

.c.o:
			@${CC} -c ${CFLAGS} $< -o ${<:.c=.o}
			@$(eval STEP=$(shell echo $$(($(STEP)+1))))

${NAME}:	${OBJS}
			@ar rc ${NAME} ${OBJS}

clean:
			@${RM} ${OBJS}

fclean:		clean
			@${RM} ${NAME}

re:			fclean
			@${MAKE} all

all:		${NAME}

.PHONY: clean, fclean, re, all

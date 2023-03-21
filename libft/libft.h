/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguerin <tguerin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:49:42 by tguerin           #+#    #+#             */
/*   Updated: 2023/02/28 14:58:50 by tguerin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

// -----------------------------------char----------------------------------- //

int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);

// --------------------------------ft_fprintf-------------------------------- //

int			ft_fprintf(int fd, const char *format, ...);

// -----------------------------ft_get_next_line----------------------------- //

char		*ft_get_next_line(int fd);

// -----------------------------------math----------------------------------- //

int			ft_abs(int x);
double		ft_dabs(double x);

// ----------------------------------memory---------------------------------- //

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);

// -----------------------------------put------------------------------------ //

void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);

// ----------------------------------splits---------------------------------- //

int			ft_split_append(char ***split, const char *value);
int			ft_split_count(char **split, const char *s);
char		**ft_split_dup(char **split);
void		ft_split_free(char **split);
char		*ft_split_join(char **split, const char *sep);
int			ft_split_len(char **split);
void		ft_split_print(char **split);
int			ft_split_remove(char ***split, int index);
int			ft_split_size(char **split);
char		**ft_split_slice(char **split, int begin, int end);
void		ft_split_sort(char **split, int case_sensitive);
char		**ft_split(char const *s, char c);

// ----------------------------------string---------------------------------- //

int			ft_atoi(const char *nptr, int *error_flag);
long		ft_atol(const char *nptr, int *error_flag);
char		*ft_itoa(int n);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strchr(const char *s, int c);
int			ft_strcount(char *s, char c);
char		*ft_strdup(const char *s);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
void		ft_strrem(char *s, int index);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);

#endif

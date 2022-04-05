/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbremond <pbremond@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 09:36:17 by pbremond          #+#    #+#             */
/*   Updated: 2022/04/04 15:22:56 by pbremond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# define MAX_FD	FOPEN_MAX

# ifdef __linux__
#  include "portability.h"
# endif

// ========================================================================== //
//                               STRING HANDLING                              //
// ========================================================================== //

// Creation
char		*ft_strnew(size_t size);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
// Addition/Fusion
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_stradd(char *s1, char const *s2);
char		*ft_stradd2(char *s1, char *s2, int choose_free);
// Copy
char		*ft_strncpy(char *dest, const char *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
// Concatenation
char		*ft_strncat(char *dest, const char *src, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
// Comparison
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strequ(char const *s1, char const *s2);
int			ft_strnequ(char const *s1, char const *s2, size_t n);
// Search
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t n);
// Checking
size_t		ft_strlen(const char *s);
size_t		ft_strlenc(char const *str, char c);
int			ft_strsum(char *str, int (*f)(char));
int			ft_strchk(char *str, int (*f)(char));
// Modification
void		ft_striter(char *s, void (*f)(char *));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strmap(char const *s, char (*f)(char));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strtrim(char const *s1, char const *set);
void		ft_strrep(char **old, char *new);
// Splitting/tokenizing
char		**ft_split(char const *s, char c);
char		**ft_split_chrst(char *str, char *charset);
char		**ft_split_free(char **array, int count);
// Deletion
void		ft_strclr(char *s);
void		ft_strdel(char **as);

// ========================================================================== //
//                                CHAR CHECKING                               //
// ========================================================================== //

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);

// ========================================================================== //
//                                LINKED LISTS                                //
// ========================================================================== //

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

// Creation
t_list		*ft_lstnew(void *content);
// Order manipulation
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstadd_front(t_list **alst, t_list *new);
t_list		*ft_lstfuze(t_list **front, t_list **back);
t_list		*ft_lstextr(t_list **lst, size_t start, size_t len);
t_list		*ft_lstinser(t_list *dest, size_t index, t_list **src);
// Content manipulation
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
// Checking
int			ft_lstsize(t_list *lst);
// Finding
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstgetn(t_list *lst, size_t n);
// Deletion
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));

// Unused linked list type, contains size information with content
typedef struct s_list_size
{
	void				*content;
	size_t				content_size;
	struct s_list_size	*next;
}				t_list_size;

t_list_size	*ft_lstnew_size(void const *content, size_t content_size);

// ========================================================================== //
//                                  PRINTING                                  //
// ========================================================================== //

// Char printing
void		ft_putchar(char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putchar_clr(char c, const char *color, int reset);
// String printing
void		ft_putstr(char const *s);
void		ft_putstr_fd(char const *s, int fd);
void		ft_putendl(char const *s);
void		ft_putendl_fd(char const *s, int fd);
// Number printing
void		ft_putnbr(int n);
void		ft_putnbr_base(int nbr, char *base);
void		ft_putnbr_base_noc(int nbr, char *base);
void		ft_putnbr_fd(int n, int fd);
// ft_printf
int			ft_printf(const char *str, ...);
int			ft_dprintf(int fd, const char *str, ...);

// ft_printf internal utilities
# define BASE_HEXA_UPPER "0123456789ABCDEF"
# define BASE_HEXA_LOWER "0123456789abcdef"
# define BASE_DECI "0123456789"

typedef union s_printf_arg
{
	int				d;
	unsigned int	u;
	char			*s;
	void			*p;
}				t_printf_arg;

typedef struct s_basic_str
{
	char	*str;
	size_t	len;
}				t_ftstr;

char		*printf_get_string(char *s);
t_ftstr		printf_gets_until_modulo(const char *str, size_t *i);
t_ftstr		ft_printf_xtract_arg(va_list va_args, const char *str, size_t *i);

// ========================================================================== //
//                             MEMORY MANAGEMENT                              //
// ========================================================================== //

// Allocation
void		*ft_memalloc(size_t size);
void		*ft_realloc(void *ptr, size_t oldsize, size_t size);
void		*ft_calloc(size_t count, size_t size);
// Manipulation
void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memccpy(void *dest, const void *src, int c, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
// Search
void		*ft_memchr(const void *s, int c, size_t n);
// Comparison
int			ft_memcmp(const void *s1, const void *s2, size_t n);
// De-allocation
void		ft_memdel(void **ap);

// ========================================================================== //
//                                    MISC                                    //
// ========================================================================== //

// int <-> char convertions
int			ft_atoi(const char *nptr);
char		*ft_itoa(int n);
char		*ft_imaxtoa_base(intmax_t n, char *base);
char		*ft_uimaxtoa_base(uintmax_t n, char *base);
// Char convertion
int			ft_toupper(int c);
int			ft_tolower(int c);

// get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 255
# endif

char		*get_next_line(int fd);

#endif

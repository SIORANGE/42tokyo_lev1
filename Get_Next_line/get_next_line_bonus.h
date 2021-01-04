/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakesat <ktakesat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:06:55 by ktakesat          #+#    #+#             */
/*   Updated: 2020/12/17 18:54:41 by ktakesat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# define RM_NODE 10
# define RM_LIST 100
# define FAILED -1
# define E_O_F 0
# define FALSE 0
# define NO_NEWLINE 0
# define SUCCESS 1
# define NORMAL 1
# define NEWLINE 1

# include <unistd.h>
# include <stdlib.h>

typedef struct		s_list
{
	int					fd;
	char				*s;
	struct s_list		*next;
	struct s_list		*prev;
}					t_list;

void				ft_lstrm(t_list **lst, int flag);
t_list				*find_fd(int fd, t_list *file);
size_t				ft_strlen(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char *s1, char *s2);

int					store_lines(char **s, char **line);
int					search_newline(char **s);
int					get_next_line(int fd, char **line);
int					make_line(t_list *node, char **line);

#endif

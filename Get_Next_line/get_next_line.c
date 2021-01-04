/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakesat <ktakesat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 01:15:45 by ktakesat          #+#    #+#             */
/*   Updated: 2020/12/31 01:20:19 by ktakesat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			store_lines(char **s, char **line)
{
	size_t		index;
	char		*temp;

	index = 0;
	while ((*s)[index] != '\n' && (*s)[index])
		index++;
	if (!(*line = ft_substr(*s, 0, index)))
		return (FAILED);
	temp = *s;
	if (!(*s = ft_substr(*s, index + 1, ft_strlen(*s) - index)))
		return (FAILED);
	free(temp);
	return (SUCCESS);
}

int			search_newline(char **s)
{
	int index;

	index = 0;
	if (!*s)
	{
		if (!(*s = (char *)malloc(sizeof(char) * 1)))
			return (FAILED);
		**s = '\0';
	}
	while ((*s)[index])
	{
		if ((*s)[index] == '\n')
			return (NEWLINE);
		index++;
	}
	return (NO_NEWLINE);
}

int			make_line(t_list *node, char **line)
{
	char		*buf;
	long long	size;
	int			check;

	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (FAILED);
	check = search_newline(&(node->s));
	size = 1;
	while ((check == NO_NEWLINE) && (size = read(node->fd, buf, BUFFER_SIZE)))
	{
		if (size < 0)
		{
			free(buf);
			return (FAILED);
		}
		buf[size] = '\0';
		node->s = ft_strjoin(node->s, buf);
		check = search_newline(&buf);
	}
	free(buf);
	if (check != FAILED)
		check = store_lines(&(node->s), line);
	if (size == 0)
		return (E_O_F);
	return (check != FAILED ? SUCCESS : FAILED);
}

int			get_next_line(int fd, char **line)
{
	static t_list	*file;
	t_list			*now_list;
	int				res;

	if (!line || BUFFER_SIZE <= 0 || fd < 0)
		return (FAILED);
	if (file == NULL)
	{
		if (!(file = (t_list *)malloc(sizeof(t_list))))
			return (FAILED);
		*file = (t_list){.fd = fd, .s = NULL, .next = NULL, .prev = NULL};
	}
	now_list = find_fd(fd, file);
	res = make_line(now_list, line);
	if (res == FAILED)
		ft_lstrm(&file, RM_LIST);
	if (res == E_O_F)
	{
		ft_lstrm(&now_list, RM_NODE);
		file = now_list;
	}
	return (res);
}

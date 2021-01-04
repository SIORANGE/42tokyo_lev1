/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktakesat <ktakesat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 01:15:03 by ktakesat          #+#    #+#             */
/*   Updated: 2021/01/02 14:20:57 by ktakesat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char				*ft_strjoin(char *s1, char *s2)
{
	char			*str;
	unsigned int	index_1;
	unsigned int	index_2;
	unsigned int	size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	index_1 = 0;
	index_2 = 0;
	while (s1[index_1])
	{
		str[index_1] = s1[index_1];
		index_1++;
	}
	while (s2[index_2])
	{
		str[index_2 + index_1] = s2[index_2];
		index_2++;
	}
	str[index_2 + index_1] = '\0';
	free(s1);
	return (str);
}

size_t				ft_strlen(const char *s)
{
	size_t len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

t_list				*find_fd(int fd, t_list *file)
{
	t_list	*temp;

	while (file->prev != NULL)
		file = file->prev;
	while (file->fd != fd)
	{
		if (file->next == NULL)
		{
			temp = file;
			if (!(file = (t_list *)malloc(sizeof(t_list))))
				return (NULL);
			*file = (t_list){.fd = fd, .s = NULL, .next = NULL, .prev = temp};
			temp->next = file;
			return (file);
		}
		file = file->next;
	}
	return (file);
}

char				*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	index;
	size_t			size;
	char			*new_str;

	if (!s)
		return (NULL);
	index = 0;
	size = 0;
	if (!(new_str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s[index])
	{
		if (start <= index && size < len)
		{
			new_str[size] = s[index];
			size++;
		}
		index++;
	}
	new_str[size] = '\0';
	return (new_str);
}

void				ft_lstrm(t_list **lst, int flag)
{
	t_list			*temp;

	if (!lst || !*lst)
		return ;
	if (flag == RM_LIST && *lst)
	{
		while ((*lst)->prev != NULL)
			*lst = (*lst)->prev;
		while (flag == RM_LIST && *lst)
		{
			temp = (*lst)->next;
			free((*lst)->s);
			free(*lst);
			*lst = temp;
		}
	}
	if (flag == RM_NODE && *lst)
	{
		if ((*lst)->prev)
			(*lst)->prev->next = (*lst)->next;
		if ((*lst)->next)
			(*lst)->next->prev = (*lst)->prev;
		temp = ((*lst)->prev) ? (*lst)->prev : (*lst)->next;
		free((*lst)->s);
		free(*lst);
		*lst = temp;
	}
}

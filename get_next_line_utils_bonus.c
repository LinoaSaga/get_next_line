/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:01:05 by ljudd             #+#    #+#             */
/*   Updated: 2025/05/02 15:19:25 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/* function to free if not null and return VOID*/
/* exist just to gain some lines in other functions*/
void	ft_gnl_free2(void *elem)
{
	if (elem)
		free(elem);
	return ;
}

/* function to create a node given the file descriptor*/
/* free memory and return NULL in case of malloc error*/
t_list_gnl	*ft_gnl_createfd(int fd)
{
	t_list_gnl	*res;

	res = (t_list_gnl *) malloc(sizeof(t_list_gnl));
	if (!res)
		return (NULL);
	res->buffer = (char *) malloc(BUFFER_SIZE * sizeof(char));
	if (!res->buffer)
	{
		free(res);
		return (NULL);
	}
	res->fd = fd;
	res->next = NULL;
	res->n_read = 0;
	return (res);
}

/*function to get the node related to the file description*/
/*if the node doesn't exist, create it and add it to the back of the list*/
/* doesnt change the list and return NULL in case of malloc error*/
t_list_gnl	*ft_gnl_getfd(int fd, t_list_gnl **buffer_list)
{
	t_list_gnl	*cur_node;

	if (!(*buffer_list))
	{
		cur_node = ft_gnl_createfd(fd);
		if (!cur_node)
			return (NULL);
		*buffer_list = cur_node;
		return (cur_node);
	}
	cur_node = *buffer_list;
	while (cur_node->fd != fd && cur_node->next)
		cur_node = cur_node->next;
	if (cur_node->fd == fd)
		return (cur_node);
	cur_node->next = ft_gnl_createfd(fd);
	return (cur_node->next);
}

/* function to free the node of the given fd once we reach EOF*/
/* also return res, just to gain a line in the core function*/
/* function suppose the node exist*/
char	*ft_gnl_freefd(int fd, t_list_gnl **buffer_list, char *res)
{
	t_list_gnl	*cur_node;
	t_list_gnl	*tmp;

	cur_node = *buffer_list;
	if (cur_node->fd == fd)
	{
		*buffer_list = cur_node->next;
		free(cur_node->buffer);
		free(cur_node);
		return (res);
	}
	while (cur_node->next->fd != fd)
		cur_node = cur_node->next;
	tmp = cur_node->next;
	cur_node->next = cur_node->next->next;
	free(tmp->buffer);
	free(tmp);
	return (res);
}

/* function that returns 1 if the next line is found, 0 otherwise*/
char	ft_gnl_findnxtline(t_list_gnl *fd_node)
{
	size_t	k;

	k = 0;
	while (k < (size_t) fd_node->n_read)
	{
		if ((fd_node->buffer)[k] == '\n')
			return (1);
		k++;
	}
	return (0);
}

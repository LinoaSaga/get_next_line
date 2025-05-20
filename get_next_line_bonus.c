/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:00:37 by ljudd             #+#    #+#             */
/*   Updated: 2025/05/20 17:52:14 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_gnl_strlen(char *s)
{
	size_t	k;

	if (!s)
		return (0);
	k = 0;
	while (s[k])
		k++;
	return (k);
}

size_t	ft_gnl_buflen(t_list_gnl *fd_node)
{
	size_t	res;

	res = 0;
	while (res < (size_t) fd_node->n_read && (fd_node->buffer)[res] != '\n')
		res++;
	if (res != (size_t) fd_node->n_read && fd_node->n_read > 0
		&& (fd_node->buffer)[res] == '\n')
		res++;
	return (res);
}

/* function that appends to the result the content of the buffer*/
/* up to the \n only if one was found, entirely otherwise*/
/* if the buffer is empty, dont copy anything*/
/* s is free and set to NULL in case of a malloc problem*/
void	ft_gnl_add(char **s, t_list_gnl *fd_node)
{
	char	*tmp;
	size_t	k;
	size_t	size_s;
	size_t	size_buf;

	if (fd_node->n_read < 1)
		return ;
	size_s = ft_gnl_strlen(*s);
	size_buf = ft_gnl_buflen(fd_node);
	tmp = (char *) malloc((size_s + size_buf + 1) * sizeof(char));
	if (!tmp)
		return (free(*s));
	k = -1;
	while (++k < size_s && *s)
		tmp[k] = (*s)[k];
	k = -1;
	while (++k < size_buf)
		tmp[size_s + k] = (fd_node->buffer)[k];
	tmp[size_s + k] = '\0';
	free(*s);
	*s = tmp;
}

/*function that removes char up to the \n included*/
void	ft_gnl_rm(t_list_gnl **fd_node)
{
	size_t	k;
	size_t	pos_n;

	pos_n = 0;
	while (((*fd_node)->buffer)[pos_n] != '\n'
		&& pos_n < (size_t)(*fd_node)->n_read)
		pos_n++;
	(*fd_node)->n_read = (*fd_node)->n_read - pos_n - 1;
	k = -1;
	while (++k < (size_t)(*fd_node)->n_read)
		((*fd_node)->buffer)[k] = ((*fd_node)->buffer)[k + pos_n + 1];
}

char	*get_next_line(int fd)
{
	static t_list_gnl	*buffer_list;
	t_list_gnl			*fd_node;
	char				*res;

	res = NULL;
	fd_node = ft_gnl_getfd(fd, &buffer_list);
	if (!fd_node)
		return (NULL);
	while (!ft_gnl_findnxtline(fd_node))
	{
		ft_gnl_add(&res, fd_node);
		if (fd_node->n_read > 0 && !res)
			return (NULL);
		fd_node->n_read = read(fd, fd_node->buffer, BUFFER_SIZE);
		if (fd_node->n_read < 0)
		{
			free(res);
			return (ft_gnl_freefd(fd, &buffer_list, NULL));
		}
		else if (fd_node->n_read == 0)
			return (ft_gnl_freefd(fd, &buffer_list, res));
	}
	ft_gnl_add(&res, fd_node);
	ft_gnl_rm(&fd_node);
	if (fd_node->n_read == 0)
		return (ft_gnl_freefd(fd, &buffer_list, res));
	return (res);
}

/* read of 3 files*/
/*int	main(int argc, char **argv)
{
	int		fd1;
	char	*line1;
	int		fd2;
	char	*line2;
	int		fd3;
	char	*line3;

	(void) argc;
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	fd3 = open(argv[3], O_RDONLY);
	line1 = get_next_line(fd1);
	line2 = get_next_line(fd2);
	line3 = get_next_line(fd3);
	while (line1)
	{
		printf("%s", line1);
		free(line1);
		line1 = get_next_line(fd1);
	}
	while (line2)
	{
		printf("%s", line2);
		free(line2);
		line2 = get_next_line(fd2);
	}
	while (line3)
	{
		printf("%s", line3);
		free(line3);
		line3 = get_next_line(fd3);
	}
	close (fd1);
	close (fd2);
	close (fd3);
}*/

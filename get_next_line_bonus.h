/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:04:03 by ljudd             #+#    #+#             */
/*   Updated: 2025/05/02 15:22:23 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE = 100
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_list_gnl
{
	char				*buffer;
	int					fd;
	ssize_t				n_read;
	struct s_list_gnl	*next;
}	t_list_gnl;

/* get_next_line_bonus.c*/
size_t		ft_gnl_strlen(char *s);
size_t		ft_gnl_buflen(t_list_gnl *fd_node);
void		ft_gnl_add(char **s, t_list_gnl *fd_node);
void		ft_gnl_rm(t_list_gnl **fd_node);
char		*get_next_line(int fd);

/* get_next_line_utils_bonus.c*/
void		ft_gnl_free2(void *elem);
t_list_gnl	*ft_gnl_createfd(int fd);
t_list_gnl	*ft_gnl_getfd(int fd, t_list_gnl **buffer_list);
char		*ft_gnl_freefd(int fd, t_list_gnl **buffer_list, char *res);
char		ft_gnl_findnxtline(t_list_gnl *fd_node);

#endif
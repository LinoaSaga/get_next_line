/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:04:03 by ljudd             #+#    #+#             */
/*   Updated: 2025/05/01 16:21:48 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE = 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_list_gnl
{
	char				*buffer;
	int					fd;
	struct s_list_gnl	*next;
}	t_list_gnl;

/* get_next_line.c*/
char	*get_next_line(int fd);

/* get_next_line_utils.c*/

#endif
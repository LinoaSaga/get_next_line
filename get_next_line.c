/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljudd <ljudd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:00:37 by ljudd             #+#    #+#             */
/*   Updated: 2025/05/01 16:19:22 by ljudd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list_gnl	buffer_list;
	char				*buffer;
	char				*res;
	int					n_read;

	res = NULL
	if (!ft_gnl_get(buffer_list, fd))
		ft_gnl_createfd(fd);
	buffer = ft_gnl_get(buffer_list, fd);
	while (!ft_gnl_findnxt(buffer_list, fd))
	{
		ft_gnl_add(ft_gnl_get(buffer_list, fd))
		n_read = read(fd, ft_gnl_get(buffer_list, fd), BUFFER_SIZE)
		if (n_read == -1 || n_read == 0)
			return (res);
	}
}

int	main(void)
{
	char	*file = "test";
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltsaros <abuzdin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:42:07 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/15 11:49:00 by baltsaros        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_line_args(char	*args)
{
	int		fd;
	char	*tmp;
	char	*line;

	fd = open(args, O_RDONLY);
	error_check_exit(fd, "open", NULL);
	tmp = get_next_line(fd);
	line = cub_strdup(tmp, NULL);
	while (tmp != NULL)
	{
		tmp = get_next_line(fd);
		if (tmp == NULL)
			break ;
		line = ft_freestrjoin(line, tmp);
		free(tmp);
	}
	close(fd);
	return (line);
}

char	**get_args_map(char	*args)
{
	int		i;
	char	*line;
	char	**args_map;

	i = 0;
	line = get_line_args(args);
	if (!line)
		print_error_and_exit(strerror(errno));
	args_map = ft_split(line, '\n');
	if (!args_map)
		free_error_and_exit(line, strerror(errno));
	free(line);
	return (args_map);
}

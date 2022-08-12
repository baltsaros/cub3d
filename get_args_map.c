/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:42:07 by mthiry            #+#    #+#             */
/*   Updated: 2022/05/16 11:18:30 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*get_line_args(char	*args)
{
	int		fd;
	char	*tmp;
	char	*line;

	fd = open(args, O_RDONLY);
	if (fd == -1)
		print_error_and_exit(strerror(errno));
	tmp = get_next_line(fd);
	line = ft_strdup(tmp);
	free(tmp);
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

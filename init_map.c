/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:13:40 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/15 15:52:26 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*find_param(char **raw, char *param)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(param);
	while (raw[i] && ft_strncmp(raw[i], param, len))
		++i;
	if (!raw[i])
		return (NULL);
	return (raw[i]);
}

void	check_param(t_map *map, t_input *data)
{
	map->no = find_param(map->raw, "NO");
	map->so = find_param(map->raw, "SO");
	map->we = find_param(map->raw, "WE");
	map->ea = find_param(map->raw, "EA");
	map->f = find_param(map->raw, "F");
	map->c = find_param(map->raw, "C");
	if (!map->no || !map->so || !map->we
		|| !map->ea || !map->f || !map->c)
		error_exit(data, "Invalid parameter(s)");
}

t_map	read_map(t_input *data, char *file)
{
	t_map	map;
	char	*buf;
	char	*line;

	buf = cub_strdup("", data);
	data->fd = open(file, O_RDONLY);
	error_check_exit(data->fd, "open", data);
	while (19)
	{
		line = get_next_line(data->fd, data);
		if (!line)
			break ;
		buf = cub_strjoin_free(buf, line, data);
		free(line);
	}
	map.raw = ft_split(buf, '\n');
	alloc_check_big(map.raw, data);
	free(buf);
	close(data->fd);
	return (map);
}

void	check_extension(t_input *data, char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 5)
		error_exit(data, "Invalid map extension");
	if (ft_strcmp(file + len - 4, ".cub"))
		error_exit(data, "Invalid map extension");
}

int	init_map(t_input *data, char *file)
{
	data->map.raw = NULL;
	check_extension(data, file);
	data->map = read_map(data, file);
	check_param(&(data->map), data);
	return (0);
}

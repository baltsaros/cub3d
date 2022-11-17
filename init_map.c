/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:13:40 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/17 08:37:44 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vars(t_data *data)
{
	data->map.raw = NULL;
	data->map.no = NULL;
	data->map.so = NULL;
	data->map.we = NULL;
	data->map.ea = NULL;
	data->map.f = NULL;
	data->map.c = NULL;
	data->map.map = NULL;
	data->map.f_spl = NULL;
	data->map.c_spl = NULL;
	data->map.width = 0;
	data->map.height = 0;
}

void	check_extension(t_data *data, char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 5)
		error_exit(data, "Invalid map extension", 0);
	if (ft_strcmp(file + len - 4, ".cub"))
		error_exit(data, "Invalid map extension", 0);
}

void	check_param(t_map *map, t_data *data)
{
	data->j = 0;
	data->map.map = NULL;
	data->map.f_spl = NULL;
	data->map.c_spl = NULL;
	map->no = find_param(map->raw, "NO", data);
	map->so = find_param(map->raw, "SO", data);
	map->we = find_param(map->raw, "WE", data);
	map->ea = find_param(map->raw, "EA", data);
	map->f = find_param(map->raw, "F", data);
	map->c = find_param(map->raw, "C", data);
	if (!map->no || !map->so || !map->we
		|| !map->ea || !map->f || !map->c)
		error_exit(data, "Invalid parameter(s)", 1);
	map->f_spl = ft_split(map->f, ',');
	map->c_spl = ft_split(map->c, ',');
	alloc_check_big(map->f_spl, data);
	alloc_check_big(map->c_spl, data);
	copy_map(map->raw, data);
	check_map(map, data);
}

t_map	read_param(t_data *data, char *file)
{
	t_map	map;
	char	*buf;
	char	*line;

	buf = cub_strdup("", data);
	data->fd = open(file, O_RDONLY);
	error_check_exit(data->fd, "open: ", data);
	data->i = 19;
	while (data->i)
	{
		line = get_next_line(data->fd, data);
		if (!line)
			break ;
		buf = cub_strjoin_free(buf, line, data);
		free(line);
	}
	map.raw = ft_split(buf, '\n');
	free(buf);
	close(data->fd);
	alloc_check_big(map.raw, data);
	return (map);
}

int	init_map(t_data *data, char *file)
{
	init_vars(data);
	check_extension(data, file);
	data->map = read_param(data, file);
	check_param(&(data->map), data);
	print_map(data, data->map.map);
	return (0);
}

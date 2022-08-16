/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:13:40 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/16 12:08:53 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vars(t_input *data)
{
	data->map.raw = NULL;
	data->map.no = NULL;
	data->map.so = NULL;
	data->map.we = NULL;
	data->map.ea = NULL;
	data->map.f = NULL;
	data->map.c = NULL;
	data->map.map = NULL;
}

char	*find_param(char **raw, char *param, t_input *data)
{
	size_t	i;
	size_t	len;
	char	**tmp;
	char	*ret;

	i = 0;
	len = ft_strlen(param);
	while (raw[i] && ft_strncmp(raw[i], param, len))
		++i;
	if (!raw[i])
		return (NULL);
	if (i > data->j)
		data->j = i;
	tmp = ft_split(raw[i], ' ');
	alloc_check_big(tmp, data);
	ret = cub_strdup(tmp[1], data);
	cub_free(tmp);
	return (ret);
}

void	check_chars(char **raw, t_input *data)
{
	size_t	j;
	size_t	i;

	j = 0;
	while (raw[j])
	{
		i = 0;
		while (raw[j][i])
		{
			if (!check_charset(raw[j][i], "10NSEW "))
				error_exit(data, "Ivalid character on the map", 1);
			++i;
		}
		++j;
	}
}

void	check_lines(char **map, t_input *data)
{
	size_t	j;
	size_t	i;
	int		closed;

	j = 0;
	closed = 1;
	while (map[j])
	{
		i = 0;
		while (map[j][i] && map[j][i] == ' ')
			++i;
		if (map[j][i] && map[j][i] != '1')
			error_exit(data, "Unclosed map", 1);
		while (map[j][i])
		{
			if (map[j][i] == '1')
				closed = 1;
			else if (map[j][i] == '0')
				closed = 0;
			i++;
		}
		if (!closed)
			error_exit(data, "Unclosed map", 1);
		++j;
	}
}

size_t	check_length(char **map, size_t i, t_input *data)
{
	size_t	j;
	size_t	len;

	j = data->j;
	while (map[j])
	{
		len = ft_strlen(map[j]);
		if (i < len)
			break ;
		++j;
	}
	data->j = j;
	return (j);
}

void	check_rows(char **map, t_input *data)
{
	size_t	j;
	size_t	i;
	int		closed;

	j = 0;
	data->j = 0;
	closed = 1;
	i = 0;
	while (map[j])
	{
		while (map[j][i] && map[j][i] == ' ')
			++j;
		if (map[j][i] && map[j][i] != '1')
			error_exit(data, "Unclosed map 2", 1);
		while (map[j] && map[j][i])
		{
			if (map[j][i] == '1')
				closed = 1;
			else if (map[j][i] == '0')
				closed = 0;
			j++;
		}
		if (!closed)
			error_exit(data, "Unclosed map", 1);
		++i;
		j = check_length(map, i, data);
	}
}

void	check_map(t_map *map, t_input *data)
{
	check_chars(map->map, data);
	printf("checking lines\n");
	check_lines(map->map, data);
	printf("checking rows\n");
	check_rows(map->map, data);
	printf("closed\n");
}

size_t	find_mapsize(char **raw, int j)
{
	size_t	size;

	size = 0;
	while (raw[j])
	{
		++size;
		++j;
	}
	return (size);
}

void	copy_map(char **raw, t_input *data)
{
	size_t	j;
	size_t	i;
	size_t	size;

	data->j++;
	j = data->j;
	if (!raw[j])
		error_exit(data, "There is no map!", 1);
	while (raw[j] && !ft_strchr(raw[j], '1'))
		++j;
	if (!raw[j])
		error_exit(data, "Invalid map!", 1);
	i = 0;
	size = find_mapsize(raw, j);
	data->map.map = cub_malloc(sizeof(char*) * (size + 1), data);
	while (raw[j + i])
	{
		data->map.map[i] = cub_strdup(raw[j + i], data);
		++i;
	}
	data->map.map[i] = NULL;
}

void	check_param(t_map *map, t_input *data)
{
	data->j = 0;
	data->map.map = NULL;
	map->no = find_param(map->raw, "NO", data);
	map->so = find_param(map->raw, "SO", data);
	map->we = find_param(map->raw, "WE", data);
	map->ea = find_param(map->raw, "EA", data);
	map->f = find_param(map->raw, "F", data);
	map->c = find_param(map->raw, "C", data);
	if (!map->no || !map->so || !map->we
		|| !map->ea || !map->f || !map->c)
		error_exit(data, "Invalid parameter(s)", 1);
	copy_map(map->raw, data);
	// for (int i = 0; map->map[i]; ++i)
	// 	printf("map[%d] is %s\n", i, map->map[i]);
	check_map(map, data);
}

t_map	read_param(t_input *data, char *file)
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

void	check_extension(t_input *data, char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 5)
		error_exit(data, "Invalid map extension", 0);
	if (ft_strcmp(file + len - 4, ".cub"))
		error_exit(data, "Invalid map extension", 0);
}

int	init_map(t_input *data, char *file)
{
	init_vars(data);
	check_extension(data, file);
	data->map = read_param(data, file);
	check_param(&(data->map), data);
	return (0);
}
 
 // gcc cub3d.c alloc_check.c cub_free.c cub_utils_1.c error_messages.c init_map.c libft.a
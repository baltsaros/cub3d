/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:13:40 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/16 11:50:34 by mthiry           ###   ########.fr       */
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
}

char	*find_param(char **raw, char *param, t_data *data)
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

void	check_chars(char **raw, t_data *data)
{
	size_t	j;
	size_t	i;

	j = data->j;
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

void	check_lines(char **raw, t_data *data)
{
	size_t	j;
	size_t	i;
	int		closed;

	j = data->j;
	closed = 1;
	while (raw[j])
	{
		i = 0;
		while (raw[j][i] && raw[j][i] == ' ')
			++i;
		if (raw[j][i] && raw[j][i] != '1')
			error_exit(data, "Unclosed map", 1);
		while (raw[j][i])
		{
			if (raw[j][i] == '1')
				closed = 1;
			else if (raw[j][i] == '0')
				closed = 0;
			i++;
		}
		if (!closed)
			error_exit(data, "Unclosed map", 1);
		++j;
	}
}

void	check_length(char **raw, size_t i, t_data *data)
{
	size_t	j;
	size_t	len;

	j = data->j;
	while (raw[j])
	{
		len = ft_strlen(raw[j]);
		if (i < len)
			break ;
		++j;
	}
	data->j = j;
}

void	check_rows(char **raw, t_data *data)
{
	size_t	j;
	size_t	i;
	int		closed;

	j = data->j;
	closed = 1;
	i = 0;
	while (raw[j])
	{
		while (raw[j][i] && raw[j][i] == ' ')
			++j;
		if (raw[j][i] && raw[j][i] != '1')
			error_exit(data, "Unclosed map 2", 1);
		while (raw[j] && raw[j][i])
		{
			if (raw[j][i] == '1')
				closed = 1;
			else if (raw[j][i] == '0')
				closed = 0;
			j++;
		}
		if (!closed)
			error_exit(data, "Unclosed map", 1);
		++i;
		check_length(raw, i, data);
		j = data->j;
	}
}

void	check_map(t_map *map, t_data *data)
{
	data->j++;
	check_chars(map->raw, data);
	printf("checking lines\n");
	check_lines(map->raw, data);
	printf("checking rows\n");
	check_rows(map->raw, data);
	printf("closed\n");
}

void	check_param(t_map *map, t_data *data)
{
	data->j = 0;
	map->no = find_param(map->raw, "NO", data);
	map->so = find_param(map->raw, "SO", data);
	map->we = find_param(map->raw, "WE", data);
	map->ea = find_param(map->raw, "EA", data);
	map->f = find_param(map->raw, "F", data);
	map->c = find_param(map->raw, "C", data);
	if (!map->no || !map->so || !map->we
		|| !map->ea || !map->f || !map->c)
		error_exit(data, "Invalid parameter(s)", 1);
	// for (int i = 0; map->raw[i]; ++i)
	// 	printf("raw[%d] is %s\n", i, map->raw[i]);
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

void	check_extension(t_data *data, char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 5)
		error_exit(data, "Invalid map extension", 0);
	if (ft_strcmp(file + len - 4, ".cub"))
		error_exit(data, "Invalid map extension", 0);
}

int	init_map(t_data *data, char *file)
{
	init_vars(data);
	check_extension(data, file);
	data->map = read_param(data, file);
	check_param(&(data->map), data);
	return (0);
}
 
 // gcc cub3d.c alloc_check.c cub_free.c cub_utils_1.c error_messages.c init_map.c libft.a
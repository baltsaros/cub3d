/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:09:01 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/25 21:26:46 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

///////////////////////////
// utils for check_param //
///////////////////////////
// check the map for invalid characters

void	check_chars(char **raw, t_data *data)
{
	size_t	j;
	size_t	i;

	j = 0;
	while (raw[j])
	{
		i = 0;
		while (raw[j][i])
		{
			if (!check_charset(raw[j][i], "10NEWSD "))
				error_exit(data, "Invalid character on the map", 1);
			++i;
		}
		++j;
	}
}

// find a wall texture
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

// find color setting for floor/ceiling
char	*find_param_color(char **raw, char *param, t_data *data)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*ret;

	j = 0;
	len = ft_strlen(param);
	while (raw[j] && ft_strncmp(raw[j], param, len))
		++j;
	if (!raw[j])
		return (NULL);
	if (j > data->j)
		data->j = j;
	i = 0;
	while (raw[j][i] && !ft_isdigit(raw[j][i]))
		++i;
	if (!raw[j][i])
		return (NULL);
	ret = cub_strdup(raw[j] + i, data);
	return (ret);
}

// count lines in the map
void	find_mapsize(char **raw, int j, t_data *data)
{
	size_t	h;
	size_t	w;

	h = 0;
	data->map.width = 0;
	w = 0;
	while (raw[j + h])
	{
		w = ft_strlen(raw[j + h]);
		if (w > data->map.width)
			data->map.width = w;
		++h;
	}
	data->map.height = h;
}

size_t	check_lines(char **map, size_t j, t_data *data)
{
	size_t	start;

	start = 0;
	while (map[j] && !ft_strchr(map[j], '1'))
		++j;
	start = j;
	if (!map[j])
		error_exit(data, "There is no map!", 1);
	while (map[j] && ft_strchr(map[j], '1'))
		++j;
	while (map[j])
	{
		if (ft_strchr(map[j], '1'))
			error_exit(data, "Empty line inside the map!", 1);
		++j;
	}
	return (start);
}

// copying map form raw data
void	copy_map(char **raw, t_data *data)
{
	size_t	j;
	size_t	i;
	size_t	len;

	data->j++;
	j = check_lines(raw, data->j, data);
	find_mapsize(raw, j, data);
	i = 0;
	data->map.map = cub_malloc(sizeof(char *) * (data->map.height + 1), data);
	while (raw[j + i])
	{
		data->map.map[i] = ft_calloc(data->map.width + 1, 1);
		alloc_check_small(data->map.map[i], data);
		data->map.map[i] = ft_memset(data->map.map[i], ' ', data->map.width);
		len = ft_strlen(raw[j + i]);
		data->map.map[i] = ft_memcpy(data->map.map[i], raw[j + i], len);
		++i;
	}
	data->map.map[i] = NULL;
}

void	check_map(t_map *map, t_data *data)
{
	check_chars(map->map, data);
	check_rows(map->map, data);
	check_columns(map->map, data);
	check_player(map->map, data);
	check_direction(data);
	print_map(data, data->map.map);
}

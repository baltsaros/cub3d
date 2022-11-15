#include "cub3d.h"

///////////////////////////
// utils for check_param //
///////////////////////////
// find a certain parameter from map input
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
		w = ft_strlen(raw[j]);
		if (w > data->map.width)
			data->map.width = w;
		++h;
	}
	data->map.height = h;
}

// copying map form raw data
void	copy_map(char **raw, t_data *data)
{
	size_t	j;
	size_t	i;
	size_t	len;

	data->j++;
	j = data->j;
	if (!raw[j])
		error_exit(data, "There is no map!", 1);
	while (raw[j] && !ft_strchr(raw[j], '1'))
		++j;
	if (!raw[j])
		error_exit(data, "Invalid map!", 1);
	find_mapsize(raw, j, data);
	i = 0;
	data->map.map = cub_malloc(sizeof(char*) * (data->map.height + 1), data);
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
	printf("Checking characters...\n");
	check_chars(map->map, data);
	printf("Checking rows...\n");
	check_rows(map->map, data);
	printf("Checking columns...\n");
	check_columns(map->map, data);
	printf("Checking player...\n");
	check_player(map->map, data);
	check_direction(data);
	printf("Mas has been checked!\n");
}

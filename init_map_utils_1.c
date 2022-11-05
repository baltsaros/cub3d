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

// copying map form raw data
void	copy_map(char **raw, t_data *data)
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

void	check_map(t_map *map, t_data *data)
{
	check_chars(map->map, data);
	printf("checking rows\n");
	check_rows(map->map, data);
	printf("checking columns\n");
	check_columns(map->map, data);
	printf("closed\n");
	printf("checking player\n");
	printf("width is %ld\nheight is %ld\n", data->map.width, data->map.height);
	check_player(map->map, data);
	check_direction(data);
	printf("squarification\n");
	squarification(data, map->map);
	printf("width is %ld\nheight is %ld\n", data->map.width, data->map.height);
}

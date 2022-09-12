#include "cub3d.h"

/////////////////////////
// utils for check_map //
/////////////////////////
// check the map for invalid characters
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
			if (!check_charset(raw[j][i], "10NEWS "))
				error_exit(data, "Ivalid character on the map", 1);
			++i;
		}
		++j;
	}
}

// check that all rows are closed
void	check_rows(char **map, t_input *data)
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
			error_exit(data, "Unclosed map: rows", 1);
		while (map[j][i])
		{
			if (map[j][i] == '1')
				closed = 1;
			else if (map[j][i] == '0')
				closed = 0;
			i++;
		}
		if (!closed)
			error_exit(data, "Unclosed map: rows", 1);
		++j;
	}
	data->map.height = j;
}

// check whether a line was fully checked; if so, go to another one
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
	if (len > data->map.width)
		data->map.width = len;
	return (j);
}

// check that all columns are closed
void	check_columns(char **map, t_input *data)
{
	size_t	j;
	size_t	i;
	int		closed;

	j = 0;
	data->j = 0;
	closed = 1;
	i = 0;
	data->map.width = 0;
	while (map[j])
	{
		while (map[j][i] && map[j][i] == ' ')
			++j;
		if (map[j][i] && map[j][i] != '1')
			error_exit(data, "Unclosed map: columns1", 1);
		while (map[j] && map[j][i])
		{
			if (map[j][i] == '1')
				closed = 1;
			else if (map[j][i] == '0')
				closed = 0;
			j++;
		}
		if (!closed)
			error_exit(data, "Unclosed map: columns2", 1);
		++i;
		j = check_length(map, i, data);
	}
}

void	check_player(char **map, t_input *data)
{
	size_t	j;
	size_t	i;
	int		player;

	j = 0;
	player = 0;
	while (map[j])
	{
		i = 0;
		while(map[j][i])
		{
			if (check_charset(map[j][i], "NEWS"))
			{
				player = 1;
				data->map.dir = map[j][i];
				data->px = i;
				data->py = j;
				break ;
			}
			++i;
		}
		++j;
	}
	if (!player)
		error_exit(data, "There is no player on the map!", 1);
}

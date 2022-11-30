/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:09:01 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/30 07:59:38 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/////////////////////////
// utils for check_map //
/////////////////////////

// check if c is a waill or a floor tile
int	check_wall(char c, int state)
{
	int	closed;

	closed = state;
	if (c == '1')
		closed = 1;
	else if (c == '0')
		closed = 0;
	return (closed);
}

// check if all gapes inside a map are closed
void	check_gap(char **map, size_t i, size_t j, t_data *data)
{
	if (j > 0 && map[j - 1][i] && check_charset(map[j - 1][i], "0NEWSDP"))
		error_exit(data, "Unclosed map: gap", 1);
	if (map[j + 1] && map[j + 1][i] && check_charset(map[j + 1][i], "0NEWSDP"))
		error_exit(data, "Unclosed map: gap", 1);
	if (i > 0 && map[j][i - 1] && check_charset(map[j][i - 1], "0NEWSDP"))
		error_exit(data, "Unclosed map: gap", 1);
	if (map[j][i + 1] && check_charset(map[j][i + 1], "0NEWSDP"))
		error_exit(data, "Unclosed map: gap", 1);
}

// verify door position
void	check_door(char **map, size_t i, size_t j, t_data *data)
{
	int	wall;

	wall = 0;
	data->map.door[0] = i;
	data->map.door[1] = j;
	data->door = 1;
	if (!i || !j || !map[j + 1][i] || !map[j][i + 1])
		error_exit(data, "Incorrect door placement", 1);
	if (map[j - 1][i] == '1')
		++wall;
	if (map[j + 1][i] == '1')
		++wall;
	if (map[j][i - 1] == '1')
		++wall;
	if (map[j][i + 1] == '1')
		++wall;
	if (wall == 4)
		error_exit(data, "Door is surrounder by walls!", 1);
}

// check that all rows are closed
void	check_rows(char **map, t_data *data)
{
	size_t	j;
	int		closed;

	j = 0;
	closed = 1;
	while (map[j])
	{
		data->i = skip_wspace(map, j, 0);
		if ((map[j][data->i] && map[j][data->i] != '1')
			|| (!map[j][data->i] && !closed))
			error_exit(data, "Unclosed map: rows1", 1);
		while (map[j][data->i])
		{
			closed = check_wall(map[j][data->i], closed);
			if (map[j][data->i] == ' ')
				check_gap(map, data->i, j, data);
			else if (map[j][data->i] == 'D')
				check_door(map, data->i, j, data);
			data->i++;
		}
		if (!closed)
			error_exit(data, "Unclosed map: rows2", 1);
		++j;
	}
}

// check that all columns are closed
void	check_columns(char **map, t_data *data)
{
	size_t	j;
	size_t	i;
	int		closed;

	closed = 1;
	j = 0;
	i = 0;
	while (map[j][i])
	{
		while (map[j] && map[j][i] && check_charset(map[j][i], " \f\n\r\t\v"))
			++j;
		if (map[j] && map[j][i] && map[j][i] != '1')
			error_exit(data, "Unclosed map: columns1", 1);
		while (map[j] && map[j][i])
		{
			closed = check_wall(map[j][i], closed);
			j++;
		}
		if (!closed)
			error_exit(data, "Unclosed map: columns2", 1);
		++i;
		j = 0;
	}
}

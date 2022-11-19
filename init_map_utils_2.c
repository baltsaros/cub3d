/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:09:01 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/19 12:36:41 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/////////////////////////
// utils for check_map //
/////////////////////////

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
	if (j > 0 && map[j - 1][i] && check_charset(map[j - 1][i], "0NEWS"))
		error_exit(data, "Unclosed map: gap", 1);
	if (map[j + 1] && map[j + 1][i] && check_charset(map[j + 1][i], "0NEWS"))
		error_exit(data, "Unclosed map: gap", 1);
	if (i > 0 && map[j][i - 1] && check_charset(map[j][i - 1], "0NEWS"))
		error_exit(data, "Unclosed map: gap", 1);
	if (map[j][i + 1] && check_charset(map[j][i + 1], "0NEWS"))
		error_exit(data, "Unclosed map: gap", 1);
}

// check that all rows are closed
void	check_rows(char **map, t_data *data)
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
			closed = check_wall(map[j][i], closed);
			if (map[j][i] == ' ')
				check_gap(map, i, j, data);
			i++;
		}
		if (!closed)
			error_exit(data, "Unclosed map: rows", 1);
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

void	check_player(char **map, t_data *data)
{
	size_t	j;
	size_t	i;
	int		player;

	j = 0;
	player = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (check_charset(map[j][i], "NEWS"))
			{
				player = 1;
				data->map.dir = map[j][i];
				data->map.coord[0] = i;
				data->map.coord[1] = j;
				break ;
			}
			++i;
		}
		++j;
	}
	if (!player)
		error_exit(data, "There is no player on the map!", 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:09:01 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/18 13:47:38 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	check_direction(t_data *data)
{
	if (data->map.dir == 'N')
		data->map.angle = 90;
	else if (data->map.dir == 'E')
		data->map.angle = 360;
	else if (data->map.dir == 'W')
		data->map.angle = 180;
	else if (data->map.dir == 'S')
		data->map.angle = 270;
	data->player_s.p_ang = data->map.angle;
}

void	print_map(t_data *data, char **map)
{
	size_t	i;

	i = 0;
	printf("\nDirection: %c\n", data->map.dir);
	printf("Players coord: (%d, %d)\n", data->map.coord[1], data->map.coord[0]);
	printf("Map size: %ld x %ld\n", data->map.width, data->map.height);
	printf("MAP:\n\n");
	while (map[i])
	{
		printf("%s\n", map[i]);
		++i;
	}
}

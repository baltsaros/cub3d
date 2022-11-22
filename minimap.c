/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:49:59 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/21 17:51:25 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square_coord(t_data *data, int color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i != SQUARE_SIZE / 2)
	{
		j = 0;
		while (j != SQUARE_SIZE / 2)
		{
			mlx_pixel_put_img(&data->minimap, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_door_coord_h(t_data *data, int color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	y += SQUARE_SIZE / 8;
	while (i != (SQUARE_SIZE / 4))
	{
		j = 0;
		while (j != SQUARE_SIZE / 2)
		{
			mlx_pixel_put_img(&data->minimap, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_door_coord_v(t_data *data, int color, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	x += SQUARE_SIZE / 8;
	while (i != SQUARE_SIZE / 2)
	{
		j = 0;
		while (j != SQUARE_SIZE / 4)
		{
			mlx_pixel_put_img(&data->minimap, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data, char **map, int color, t_point max)
{
	int	i;
	int	j;

	i = 0;
	while (i != max.y)
	{
		j = 0;
		while (j != max.x)
		{
			if (map[i][j] == '1')
				draw_square_coord(data, color, j * (SQUARE_SIZE / 2),
					i * (SQUARE_SIZE / 2));
			else if (map[i][j] == 'D')
			{
				if (map[i][j - 1] == '1' && map[i][j + 1] == '1')
					draw_door_coord_h(data, color, j * (SQUARE_SIZE / 2),
						i * (SQUARE_SIZE / 2));
				else if (map[i - 1][j] == '1' && map[i + 1][j] == '1')
					draw_door_coord_v(data, color, j * (SQUARE_SIZE / 2),
						i * (SQUARE_SIZE / 2));
			}
			j++;
		}
		i++;
	}
}

void	init_minimap_values(t_data *data)
{
	data->minimap_s.width = data->map.width * (SQUARE_SIZE / 2);
	data->minimap_s.height = data->map.height * (SQUARE_SIZE / 2);
	data->minimap_s.position.x = (WIDTH / 2) - (data->minimap_s.width / 2);
	data->minimap_s.position.y = 0;
}

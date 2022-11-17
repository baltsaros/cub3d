/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:49:59 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/17 16:52:58 by mthiry           ###   ########.fr       */
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

void	draw_map(t_data *data, int color, int height, int width)
{
    int i;
    int j;

    i = 0;
    while (i != height)
    {
        j = 0;
        while (j != width)
        {
            if (data->map.map[i][j] == '1')
                draw_square_coord(data, color, j * (SQUARE_SIZE / 2), i * (SQUARE_SIZE / 2));
            j++;
        }
        i++;
    }
}

void init_minimap_values(t_data *data)
{
    data->minimap_s.width = data->map.width * (SQUARE_SIZE / 2);
    data->minimap_s.height = data->map.height * (SQUARE_SIZE / 2);
    data->minimap_s.position.x = (WIDTH / 2) - (data->minimap_s.width / 2);
    data->minimap_s.position.y = 0;
}
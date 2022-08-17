/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:49:59 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/17 17:08:40 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_square_coord(t_data *data, int color, int x, int y)
{
    int i;
    int j;

    i = 0;
    while (i != 50)
    {
        j = 0;
        while (j != 50)
        {
            my_mlx_pixel_put(&data->minimap, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void    draw_empty_square_coord(t_data *data, int color, int x, int y)
{
    int i;
    int j;

    i = 0;
    while (i != 50)
    {
        j = 0;
        while (j != 50)
        {
            if (i == 0 || j == 0)
                my_mlx_pixel_put(&data->minimap, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void    draw_map(t_data *data, int color, int height, int width)
{
    (void)color;
    (void)data;
    int i;
    int j;

    i = 0;
    printf("Width draw map: %d\n", width);
    printf("Height draw map: %d\n", height);
    while (i != height)
    {
        j = 0;
        while (j != width)
        {
            if (data->map.map[i][j] == '1')
            {
                draw_square_coord(data, color, 0 + (j * 50), 0 + (i * 50));
            }
            else if (data->map.map[i][j] == '0' || data->map.map[i][j] == 'N')
            {
                draw_empty_square_coord(data, color, 0 + (j * 50), 0 + (i * 50));
            }
            j++;
        }
        i++;
    }
}
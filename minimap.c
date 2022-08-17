/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:49:59 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/17 18:25:10 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_square_coord(t_data *data, int color, int x, int y)
{
    int i;
    int j;

    i = 0;
    while (i != data->size_square)
    {
        j = 0;
        while (j != data->size_square)
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
    while (i != data->size_square)
    {
        j = 0;
        while (j != data->size_square)
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
    int i;
    int j;

    i = 0;
    while (i != height)
    {
        j = 0;
        while (j != width)
        {
            if (data->map.map[i][j] == '1')
                draw_square_coord(data, color, (j * data->size_square), (i * data->size_square));
            else if (data->map.map[i][j] == '0' || data->map.map[i][j] == 'N')
                draw_empty_square_coord(data, color, (j * data->size_square), (i * data->size_square));
            if (data->map.map[i][j] == 'N')
            {
                data->player_s.pos_x = (j * (data->size_square)) + (data->size_square / 2) - (data->size_player / 2);
                data->player_s.pos_y = (i * (data->size_square)) + (data->size_square / 2) - (data->size_player / 2);
            }
            j++;
        }
        i++;
    }
}
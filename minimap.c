/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:49:59 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/19 16:55:17 by mthiry           ###   ########.fr       */
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
            mlx_pixel_put_img(&data->minimap_s.minimap, x + j, y + i, color);
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
                mlx_pixel_put_img(&data->minimap_s.minimap, x + j, y + i, color);
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

void    init_minimap(t_data *data, t_minimap minimap)
{
    minimap.minimap.basic_color = 0x000000;
    minimap.minimap.addr = mlx_get_data_addr(minimap.minimap.img_ptr, &minimap.minimap.bpp,
        &minimap.minimap.line_length, &minimap.minimap.endian);
    draw_square(minimap.minimap, create_trgb(255, 255, 255, 255), minimap.height, minimap.width);
    // draw_map(data, minimap.minimap.basic_color, data->map.height, data->map.width);
    mlx_put_image_to_window(data->mlx, data->win, minimap.minimap.img_ptr, minimap.position.x, minimap.position.y);
}

void    init_minimap_values(t_data *data)
{
    data->minimap_s.position.x = 10;
    data->minimap_s.position.y = 10;
    data->minimap_s.width = data->map.width * data->size_square;
    data->minimap_s.height = data->map.height * data->size_square;
    data->minimap_s.minimap.img_ptr = mlx_new_image(data->mlx, data->minimap_s.width, data->minimap_s.height);
    // if (!data->minimap_s.minimap.img_ptr)
    // Do Error here
}
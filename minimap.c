/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:49:59 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/08 12:22:19 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_square_coord(t_data *data, int color, int x, int y)
{
    int i;
    int j;

    i = 0;
    while (i != SQUARE_SIZE)
    {
        j = 0;
        while (j != SQUARE_SIZE)
        {
            mlx_pixel_put_img(&data->minimap, x + j, y + i, color);
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
    while (i != SQUARE_SIZE)
    {
        j = 0;
        while (j != SQUARE_SIZE)
        {
            if (i == 0 || j == 0)
                mlx_pixel_put_img(&data->minimap, x + j, y + i, color);
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
                draw_square_coord(data, color, (j * SQUARE_SIZE), (i * SQUARE_SIZE));
            else if (data->map.map[i][j] == '0' || data->map.map[i][j] == 'N')
                draw_empty_square_coord(data, color, (j * SQUARE_SIZE), (i * SQUARE_SIZE));
            j++;
        }
        i++;
    }
}

void    init_minimap(t_data *data, t_minimap minimap)
{
    data->minimap.basic_color = 0x000000;
    data->minimap.addr = mlx_get_data_addr(data->minimap.img_ptr, &data->minimap.bpp,
        &data->minimap.line_length, &data->minimap.endian);
    ft_memset(data->minimap.addr, create_trgb(255, 255, 255, 255), minimap.height * minimap.width * sizeof(int));
    draw_map(data, data->minimap.basic_color, data->map.height, data->map.width);
    mlx_put_image_to_window(data->mlx, data->win, data->minimap.img_ptr, minimap.position.x, minimap.position.y);
}

int init_minimap_values(t_data *data)
{
    data->minimap_s.position.x = 10;
    data->minimap_s.position.y = 10;
    data->minimap_s.width = data->map.width * SQUARE_SIZE;
    data->minimap_s.height = data->map.height * SQUARE_SIZE;
    data->minimap.img_ptr = mlx_new_image(data->mlx, data->minimap_s.width, data->minimap_s.height);
    if (!data->minimap.img_ptr)
        return (1);
    return (0);
}
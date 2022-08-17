/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:25:50 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/17 16:50:15 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_square(t_img img, int color, int end_i, int end_j)
{
    int i;
    int j;

    i = 0;
    while (i != end_i)
    {
        j = 0;
        while (j != end_j)
        {
            my_mlx_pixel_put(&img, j, i, color);
            j++;
        }
        i++;
    }
}

void    init_background(t_data *data)
{
    data->img.basic_color = create_trgb(0, ft_atoi(data->map.c_spl[0]), ft_atoi(data->map.c_spl[1]), ft_atoi(data->map.c_spl[2]));
    data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
		&data->img.line_length, &data->img.endian);
    draw_square(data->img, data->img.basic_color, HEIGHT, WIDTH);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}

void    init_player(t_data *data)
{
    data->player.basic_color = 0x0FAE2;
    data->player.addr = mlx_get_data_addr(data->player.img_ptr, &data->player.bpp,
		&data->player.line_length, &data->player.endian);
    draw_square(data->player, data->player.basic_color, 10, 10);
    mlx_put_image_to_window(data->mlx, data->win, data->player.img_ptr, data->pos_x, data->pos_y);
}

void    init_map_img(t_data *data)
{
    int color;

    color = 0x000000;
    data->minimap.addr = mlx_get_data_addr(data->minimap.img_ptr, &data->minimap.bpp,
        &data->minimap.line_length, &data->minimap.endian);
    draw_square(data->minimap, data->img.basic_color, data->map.height * 50, data->map.width * 50);
    draw_map(data, color, data->map.height, data->map.width);
    mlx_put_image_to_window(data->mlx, data->win, data->minimap.img_ptr, 1, 1);
}

void    draw_all(t_data *data)
{
    data->img.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    if (data->img.img_ptr != NULL)
        init_background(data);
    //else
        // put error here
    printf("Width: %lu\n", data->map.width * 50);
    printf("Height: %lu\n", data->map.height * 50);
    data->minimap.img_ptr = mlx_new_image(data->mlx, data->map.width * 50, data->map.height * 50);
    if (data->minimap.img_ptr != NULL)
        init_map_img(data);
    // else
        // put error here
    data->player.img_ptr = mlx_new_image(data->mlx, 10, 10);
    if (data->player.img_ptr != NULL)
        init_player(data);
    //else
        // put error here
}
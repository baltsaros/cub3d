/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:25:50 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/17 13:58:41 by mthiry           ###   ########.fr       */
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

// void    draw_map(t_data *data)
// {
//     int x0;
//     int y0;
//     int x1;
//     int y1;
//     (void)data;
// }

void    draw_all(t_data *data)
{
    int color;
    
    data->img.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    if (data->img.img_ptr != NULL)
    {
        data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
		    &data->img.line_length, &data->img.endian);
        color = create_trgb(0, ft_atoi(data->map.c_spl[0]), ft_atoi(data->map.c_spl[1]), ft_atoi(data->map.c_spl[2]));
        draw_square(data->img, color, HEIGHT, WIDTH);
        mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
    }
    //else
        // put error here
    data->player.img_ptr = mlx_new_image(data->mlx, 10, 10);
    if (data->player.img_ptr != NULL)
    {
        data->player.addr = mlx_get_data_addr(data->player.img_ptr, &data->player.bpp,
		    &data->player.line_length, &data->player.endian);
        color = 0X000000;
        draw_square(data->player, color, 10, 10);
        mlx_put_image_to_window(data->mlx, data->win, data->player.img_ptr, data->pos_x, data->pos_y);
    }
    //else
        // put error here
}
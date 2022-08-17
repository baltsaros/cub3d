/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:25:50 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/17 11:53:00 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_background(t_data *data)
{
    int color;
    int i;
    int j;
    
    i = 0;
    color = create_trgb(0, 
        ft_atoi(data->map.c_spl[0]),
        ft_atoi(data->map.c_spl[1]),
        ft_atoi(data->map.c_spl[2]));
    while (i != HEIGHT)
    {
        j = 0;
        while (j != WIDTH)
        {
            my_mlx_pixel_put(&data->img, j, i, color);
            j++;
        }
        i++;
    }
}

void    draw_player(t_data *data)
{
    int     i;
    int     j;

    i = 0;
    while (i != 10)
    {
        j = 0;
        while (j != 10)
        {
            my_mlx_pixel_put(&data->player, j, i, 0x000000);
            j++;
        }
        i++;
    }
}

void    draw_all(t_data *data)
{
    data->img.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    if (data->img.img_ptr != NULL)
    {
        data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
		    &data->img.line_length, &data->img.endian);
        init_background(data);
        mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
    }
    //else
        // put error here
    data->player.img_ptr = mlx_new_image(data->mlx, 10, 10);
    if (data->player.img_ptr != NULL)
    {
        data->player.addr = mlx_get_data_addr(data->player.img_ptr, &data->player.bpp,
		    &data->player.line_length, &data->player.endian);
        draw_player(data);
        mlx_put_image_to_window(data->mlx, data->win, data->player.img_ptr, data->pos_x, data->pos_y);
    }
    //else
        // put error here
}
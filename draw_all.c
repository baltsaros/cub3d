/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:25:50 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/19 16:26:43 by mthiry           ###   ########.fr       */
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

void    init_ceiling(t_data *data)
{
    data->ceiling.basic_color = create_trgb(0,
        ft_atoi(data->map.c_spl[0]),
        ft_atoi(data->map.c_spl[1]),
        ft_atoi(data->map.c_spl[2]));
    data->ceiling.addr = mlx_get_data_addr(data->ceiling.img_ptr, &data->ceiling.bpp,
		&data->ceiling.line_length, &data->ceiling.endian);
    draw_square(data->ceiling, data->ceiling.basic_color, HEIGHT, WIDTH);
    mlx_put_image_to_window(data->mlx, data->win, data->ceiling.img_ptr, 0, 0);
}

void    draw_all(t_data *data)
{
    // Ceiling
    data->ceiling.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    if (data->ceiling.img_ptr != NULL)
        init_ceiling(data);
    //else
        // put error here
    // Minimap
    init_minimap(data, data->minimap_s);
    // Player then
    // Ray then
}
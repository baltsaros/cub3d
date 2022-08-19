/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:09:32 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/19 16:14:28 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void  draw_ray(t_data *data)
{
    t_point begin;
    t_point end;

    begin.x = data->player_s.pos_x + (data->size_player / 2);
    begin.y = data->player_s.pos_y + (data->size_player / 2);
    end.x = data->player_s.pos_x + data->player_s.delta_x * 10;
    end.y = data->player_s.pos_y + data->player_s.delta_y * 10;
    bresenham(data, begin, end, &data->ray_s.ray);
}

void  init_ray(t_data *data)
{
    data->ray_s.ray.img_ptr = mlx_new_image(data->mlx, data->minimap_s.width, data->minimap_s.height);
    // if (!data->ray_s.ray.img_ptr)
    // // Put error here
    data->ray_s.ray.basic_color = 0xFFFFFF;
    data->ray_s.ray.addr = mlx_get_data_addr(data->ray_s.ray.img_ptr, &data->ray_s.ray.bpp,
		  &data->ray_s.ray.line_length, &data->ray_s.ray.endian);
    draw_square(data->ray_s.ray, create_trgb(255, 255, 255, 255), data->minimap_s.height, data->minimap_s.width);
    draw_ray(data);
    mlx_put_image_to_window(data->mlx, data->win, data->ray_s.ray.img_ptr, data->minimap_s.position.x, data->minimap_s.position.y);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_and_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:16:23 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/18 18:24:31 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void  draw_ray(t_data *data)
{
    t_point begin;
    t_point end;

    begin.x = data->player_s.pos_x + (data->size_player / 2);
    begin.y = data->player_s.pos_y + (data->size_player / 2);
    end.x = data->player_s.pos_x + data->player_s.delta_x * 50;
    end.y = data->player_s.pos_y + data->player_s.delta_y * 50;
    bresenham(data, begin, end, &data->ray);
}

void  init_ray(t_data *data)
{
    data->ray.basic_color = 0xFFFFFF;
    data->ray.addr = mlx_get_data_addr(data->ray.img_ptr, &data->ray.bpp,
		  &data->ray.line_length, &data->ray.endian);
    draw_square(data->ray, create_trgb(255, 255, 255, 255), data->map.height * data->size_square, data->map.width * data->size_square);
    draw_ray(data);
    mlx_put_image_to_window(data->mlx, data->win, data->ray.img_ptr, data->pos_x_minimap, data->pos_y_minimap);
}

void    init_player(t_data *data)
{
    data->player.basic_color = 0x0FAE2;
    data->player.addr = mlx_get_data_addr(data->player.img_ptr, &data->player.bpp,
		  &data->player.line_length, &data->player.endian);
    draw_square(data->player, data->player.basic_color, data->size_player, data->size_player);
    data->player_s.pos_win_x = data->pos_x_minimap + data->player_s.pos_x;
    data->player_s.pos_win_y = data->pos_y_minimap + data->player_s.pos_y;
    mlx_put_image_to_window(data->mlx, data->win, data->player.img_ptr, data->player_s.pos_win_x, data->player_s.pos_win_y);
    
    data->ray.img_ptr = mlx_new_image(data->mlx, data->map.width * data->size_square, data->map.height * data->size_square);
    if (data->ray.img_ptr != NULL)
        init_ray(data);
    //else
        // put error here
}
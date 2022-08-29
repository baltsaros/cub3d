/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:18:08 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/29 12:58:06 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_vertical_line(t_data *data, t_point begin, t_point end)
{
    while (begin.y != end.y + 1)
    {   
        if (begin.x >= 0 && begin.x <= WIDTH && begin.y >= 0 && begin.y <= HEIGHT)     
            mlx_pixel_put_img(&data->walls, begin.x, begin.y, data->walls.basic_color);
        begin.y++;
    }
}

void    init_calculate_wall(t_data *data, t_ray_calcul *ray)
{
    t_point begin;
    t_point end;
    int     distProj;
    int     wallHeight;

    distProj = (WIDTH / 2) / tan(degToRad(FIELD_OF_VIEW / 2));
    wallHeight = (SQUARE_SIZE / ray->disH) * distProj;
    begin.x = ray->r * (WIDTH / FIELD_OF_VIEW);
    begin.y = (HEIGHT / 2) - (wallHeight / 2);
    end.x = begin.x;
    end.y = begin.y + wallHeight;

    // Need fix
    // for (int i = 0; i != ((ray->r + 1) * (WIDTH / FIELD_OF_VIEW)); i++)
    // {
        draw_vertical_line(data, begin, end);
        // begin.x = (ray->r * (WIDTH / FIELD_OF_VIEW)) + i;
        // end.x = begin.x;
    // }
}

void    init_wall(t_data *data)
{
    data->walls.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->walls.basic_color = 0x777777;
    data->walls.addr = mlx_get_data_addr(data->walls.img_ptr, &data->walls.bpp,
        &data->walls.line_length, &data->walls.endian);
    draw_square(data->walls, create_trgb(255, 255, 255, 255), HEIGHT, WIDTH);
    raycast(data, data->ray_calcul);
    mlx_put_image_to_window(data->mlx, data->win, data->ray.img_ptr, data->minimap_s.position.x, data->minimap_s.position.y);
    mlx_put_image_to_window(data->mlx, data->win, data->walls.img_ptr, 0, 0);
}
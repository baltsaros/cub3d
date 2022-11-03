/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:18:08 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/03 11:56:15 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_vertical_line(t_data *data, t_wall_drawing *wall, int pos)
{
    int color;

    color = 0x1E90FF;
    while (wall->begin.y != wall->end.y + 1)
    {
        if (wall->begin.x >= 0 && wall->begin.x <= WIDTH && wall->begin.y >= 0 && wall->begin.y <= HEIGHT)
        {
            if (pos == NORTH)
                mlx_pixel_put_img(&data->walls, wall->begin.x, wall->begin.y, data->walls.basic_color);
            else if (pos == WEST)
                mlx_pixel_put_img(&data->walls, wall->begin.x, wall->begin.y, data->walls.basic_color);
            else if (pos == SOUTH)
                mlx_pixel_put_img(&data->walls, wall->begin.x, wall->begin.y, color);
            else if (pos == EAST)
                mlx_pixel_put_img(&data->walls, wall->begin.x, wall->begin.y, color);
        }    
        wall->begin.y++;
    }
}

void    init_calculate_wall(t_data *data, t_ray_calcul *ray, int pos)
{
    float   distProj;
    float   wallHeight;

    distProj = (WIDTH / 2) / tan(degToRad(FIELD_OF_VIEW / 2));
    wallHeight = (SQUARE_SIZE / ray->disH) * distProj;
    data->wall_drawing.begin.x = (((float)ray->r) * ((float)WIDTH / (float)NB_RAYS));
    data->wall_drawing.begin.y = (HEIGHT / 2) - (wallHeight / 2);
    data->wall_drawing.end.x = data->wall_drawing.begin.x;
    data->wall_drawing.end.y = data->wall_drawing.begin.y + wallHeight;
    // for (int i = ray->r; i != (ray->r + 1) * (WIDTH / FIELD_OF_VIEW); i++)
    // {
        draw_vertical_line(data, &data->wall_drawing, pos);
        // begin.x = i;
        // end.x = begin.x;    
    // }
}

void    init_wall(t_data *data)
{
    data->walls.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->walls.basic_color = 0x00BFFF;
    data->walls.addr = mlx_get_data_addr(data->walls.img_ptr, &data->walls.bpp,
        &data->walls.line_length, &data->walls.endian);
    draw_square(data->walls, create_trgb(255, 255, 255, 255), HEIGHT, WIDTH);
    raycast(data, data->ray_calcul);
    mlx_put_image_to_window(data->mlx, data->win, data->ray.img_ptr, data->minimap_s.position.x, data->minimap_s.position.y);
    mlx_put_image_to_window(data->mlx, data->win, data->walls.img_ptr, 0, 0);
}
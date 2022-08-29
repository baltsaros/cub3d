/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:18:08 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/29 19:43:53 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_vertical_line(t_data *data, t_ray_calcul *ray, t_point begin, t_point end)
{
    (void)ray;
    int color;

    color = 0x1E90FF;
    // printf("ray->pos: %d\n", ray->posH);
    while (begin.y != end.y + 1)
    {
        if (begin.x >= 0 && begin.x <= WIDTH && begin.y >= 0 && begin.y <= HEIGHT)
        {
            // if (ray->posH == NORTH || ray->posH == WEST)
                mlx_pixel_put_img(&data->walls, begin.x, begin.y, data->walls.basic_color);
            // else if (ray->posH == SOUTH || ray->posH == EAST)
                // mlx_pixel_put_img(&data->walls, begin.x, begin.y, color);
        }    
        begin.y++;
    }
}

void    init_calculate_wall(t_data *data, t_ray_calcul *ray)
{
    int     distProj;
    int     wallHeight;

    distProj = (WIDTH / 2) / tan(degToRad(FIELD_OF_VIEW / 2));
    wallHeight = (SQUARE_SIZE / ray->disH) * distProj;
    data->wall_drawing.begin.x = ((ray->r) * (WIDTH / NB_RAYS));
    data->wall_drawing.begin.y = (HEIGHT / 2) - (wallHeight / 2);
    data->wall_drawing.end.x = data->wall_drawing.begin.x;
    data->wall_drawing.end.y = data->wall_drawing.begin.y + wallHeight;
    // for (int i = ray->r; i != (ray->r + 1) * (WIDTH / FIELD_OF_VIEW); i++)
    // {
        draw_vertical_line(data, ray, data->wall_drawing.begin, data->wall_drawing.end);
        // begin.x = i;
        // end.x = begin.x;    
    // }
    if (ray->r != 0)
    {
        bresenham(data, data->wall_drawing.begin, data->wall_drawing.old_begin, &data->walls);
        bresenham(data, data->wall_drawing.end, data->wall_drawing.old_end, &data->walls);
    }
    data->wall_drawing.old_begin.x = data->wall_drawing.begin.x;
    data->wall_drawing.old_begin.y = data->wall_drawing.begin.y;
    data->wall_drawing.old_end.x = data->wall_drawing.end.x;
    data->wall_drawing.old_end.y = data->wall_drawing.end.y;
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:09:32 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/22 16:41:10 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    calculate_ray(t_data *data)
{
    int     r;
    int     mx;
    int     my;
    int     mp;
    int     dof;
    float   rx;
    float   ry;
    float   ra;
    float   xo;
    float   yo;
    float   aTan;
    char    *map_line;

    map_line = ft_strdup("");
    for (int i = 0; data->map.map[i]; i++)
        map_line = ft_strjoin(map_line, data->map.map[i]);

    r = 0;
    ra = data->player_s.p_ang;
    while (r < 1)
    {
        // Check Horizontal Lines
        dof = 0;
        aTan = -1 / tan(ra);
        // Hit the first line
        // Looking up
        if (ra > M_PI)
        {
            ry = (((int)data->player_s.pos_x >> 6) << 6) - 0.0001;
            rx = (data->player_s.pos_y - ry) * aTan + data->player_s.pos_x;
            yo = -64;
            xo = -yo * aTan;
        }
        else if (ra < M_PI)
        {
            ry = (((int)data->player_s.pos_x >> 6) << 6) + 64;
            rx = (data->player_s.pos_y - ry) * aTan + data->player_s.pos_x;
            yo = 64;
            xo = -yo * aTan;
        }
        if (ra == 0 || ra == M_PI) // looking straight left or right
        {
            rx = data->player_s.pos_x;
            ry = data->player_s.pos_y;
            dof = 8;
        }
        while (dof < 8)
        {
            mx = (int)rx >> 6;
            my = (int)ry >> 6;
            mp = my * data->map.width + mx;
            if (mp < (int)data->map.width * (int)data->map.height && map_line[mp] == '1') // hit wall
                dof = 8;
            else
            {
                rx += xo;
                ry += yo;
                dof++;
            }
        }
        // Draw Rays
        t_point begin;
        t_point end;

        begin.x = data->player_s.pos_x + (PLAYER_SIZE / 2);
        begin.y = data->player_s.pos_y + (PLAYER_SIZE / 2);
        end.x = rx;
        end.y = ry;
        bresenham(data, begin, end, &data->ray);
        r++;
    }
}

void  draw_ray(t_data *data)
{
    calculate_ray(data);
}

void  init_ray(t_data *data)
{
    data->ray.img_ptr = mlx_new_image(data->mlx, data->minimap_s.width, data->minimap_s.height);
    // if (!data->ray_s.ray.img_ptr)
    // // Put error here
    data->ray.basic_color = 0xFFFFFF;
    data->ray.addr = mlx_get_data_addr(data->ray.img_ptr, &data->ray.bpp,
		  &data->ray.line_length, &data->ray.endian);
    draw_square(data->ray, create_trgb(255, 255, 255, 255), data->minimap_s.height, data->minimap_s.width);
    draw_ray(data);
    mlx_put_image_to_window(data->mlx, data->win, data->ray.img_ptr, data->minimap_s.position.x, data->minimap_s.position.y);
}
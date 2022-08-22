/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:09:32 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/22 18:45:09 by mthiry           ###   ########.fr       */
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
    // float   vx;
    // float   vy;
    float   Tan;
    char    *map_line;

    map_line = ft_strdup("");
    for (int i = 0; data->map.map[i]; i++)
        map_line = ft_strjoin(map_line, data->map.map[i]);
    for (int i = 0; map_line[i]; i++)
    {
        printf("[%d]: %c\n", i, map_line[i]);
    }

    r = 0;
    ra = FixAng(data->player_s.p_ang + 30);
    while (r < 1)
    {
        Tan = tan(degToRad(ra));
        // Check Horizontal Lines
        dof = 0;
        Tan = 1.0/Tan;
        // Hit the first line
        // Looking up
        if (sin(degToRad(ra)) > 0.001)
        {
            ry = (((int)data->player_s.pos_y / 64) * 64) - 0.0001;
            rx = (data->player_s.pos_y - ry) * Tan + data->player_s.pos_x;
            yo = -64;
            xo = -yo * Tan;
        }
        else if (sin(degToRad(ra)) < -0.001)
        {
            ry = (((int)data->player_s.pos_y / 64) * 64) + 64; // /64 * 64
            rx = (data->player_s.pos_y - ry) * Tan + data->player_s.pos_x;
            yo = 64;
            xo = -yo * Tan;
        }
        else // looking straight left or right
        {
            rx = data->player_s.pos_x;
            ry = data->player_s.pos_y;
            dof = 8;
        }
        // pas bon
        while (dof < 8)
        {
            printf("RX int: %d\n", (int)rx);
            printf("RY int: %d\n", (int)ry);
            mx = ((int)(rx) / 64); // >> 6
            my = ((int)(ry) / 64);
            mp = my * data->map.width + mx;
            printf("Width: %zu\n", data->map.width);
            printf("Height: %zu\n", data->map.height);
            printf("MX: %d\n", mx);
            printf("MY: %d\n", my);
            printf("MP: %d\n", mp);
            if (mp > 0 && mp < (int)data->map.width * (int)data->map.height && map_line[mp] == '1') // hit wall
                dof = 8;
            else
            {
                rx += xo;
                ry += yo;
                dof++;
            }
        }
        // Draw Rays
        printf("RX: %f\n", rx);
        printf("RY: %f\n", ry);
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
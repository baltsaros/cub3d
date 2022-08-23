/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:09:32 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/23 12:33:27 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    calculate_ray(t_data *data)
{
    int     r;
    int     mx;
    int     my;
    int     dof;
    float   rx;
    float   ry;
    float   ra;
    float   xo;
    float   yo;
    // Others values
    int     side;
    float   disV;
    float   disH;
    float   vx;
    float   vy;
    float   Tan;

    r = 0;
    ra = FixAng(data->player_s.p_ang + 30);
    while (r < 1)
    {
        // First calcul
        Tan = tan(degToRad(ra));
        side = 0;
        // Vertical
        dof = 0;
        disV = 100000;
        if (cos(degToRad(ra)) > 0.001)
        {
            rx = (((int)data->player_s.pos_x / 64) * 64) + 64;
            ry = (data->player_s.pos_x - rx) * Tan + data->player_s.pos_y;
            xo = 64;
            yo = -xo * Tan;
        }
        else if (cos(degToRad(ra)) <- 0.001)
        {
            rx = (((int)data->player_s.pos_x / 64) * 64) - 0.0001;
            ry = (data->player_s.pos_x - rx) * Tan + data->player_s.pos_y;
            xo = -64;
            yo = -xo * Tan;
        }
        else
        {
            rx = data->player_s.pos_x;
            ry = data->player_s.pos_y;
            dof = 8;
        }
        while (dof < 8)
        {
            mx=(int)(rx) / 64;
            my=(int)(ry) / 64;                 
            if (my >= 0 && mx >= 0 && data->map.map[my][mx] == '1')
            {
                dof = 8;
                disV = cos(degToRad(ra)) * (rx - data->player_s.pos_x) - sin(degToRad(ra)) * (ry - data->player_s.pos_y);
            }         
            else
            {
                rx += xo;
                ry += yo;
                dof++;
            }     
        }
        vx = rx;
        vy = ry;
        // Horizontal 
        dof = 0;
        disH = 100000;
        Tan = 1.0 / Tan;
        if (sin(degToRad(ra)) > 0.001)
        {
            ry = (((int)data->player_s.pos_y / 64) * 64) - 0.0001;
            rx = (data->player_s.pos_y - ry) * Tan + data->player_s.pos_x;
            yo = -64;
            xo = -yo * Tan;
        }
        else if (sin(degToRad(ra)) < -0.001)
        {
            ry = (((int)data->player_s.pos_y / 64) * 64) + 64;
            rx = (data->player_s.pos_y - ry) * Tan + data->player_s.pos_x;
            yo = 64;
            xo = -yo * Tan;
        }
        else
        {
            rx = data->player_s.pos_x;
            ry = data->player_s.pos_y;
            dof = 8;
        }
        while (dof < 8)
        {
            mx = ((int)(rx) / 64); // >> 6
            my = ((int)(ry) / 64);
            if (my >= 0 && mx >= 0 && data->map.map[my][mx] == '1')
            {
                dof = 8;
                disH = cos(degToRad(ra)) * (rx - data->player_s.pos_x) - sin(degToRad(ra)) * (ry - data->player_s.pos_y);
            }
            else
            {
                rx += xo;
                ry += yo;
                dof++;
            }
        }
        if (disV < disH)
        {
            rx = vx;
            ry = vy;
            disH = disV;
        }
        // Draw Rays
        t_point begin;
        t_point end;

        begin.x = data->player_s.pos_x + (PLAYER_SIZE / 2);
        begin.y = data->player_s.pos_y + (PLAYER_SIZE / 2);
        end.x = rx;
        end.y = ry;
        bresenham(data, begin, end, &data->ray);
        
        ra = FixAng(ra - 1);
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
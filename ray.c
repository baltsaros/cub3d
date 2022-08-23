/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:09:32 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/23 16:56:17 by mthiry           ###   ########.fr       */
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

void    calculate_ray(t_data *data)
{
    t_point begin;
    t_point end;
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
    while (r < FIELD_OF_VIEW)
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
            mx = (int)(rx) / 64;
            my = (int)(ry) / 64;            
            if (my >= 0 && mx >= 0 && my < (int)data->map.height && mx < (int)data->map.width - 1 && data->map.map[my][mx] == '1')
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
            if (my >= 0 && mx >= 0 && my < (int)data->map.height && mx < (int)data->map.width - 1 && data->map.map[my][mx] == '1')
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
        begin.x = data->player_s.pos_x + (PLAYER_SIZE / 2);
        begin.y = data->player_s.pos_y + (PLAYER_SIZE / 2);
        end.x = rx;
        end.y = ry;
        bresenham(data, begin, end, &data->ray);

        // int ca = FixAng(data->player_s.p_ang - ra);
        // disH = disH * cos(degToRad(ca));
        
        printf("disH: %f\n", disH);
        
        int lineH = (SQUARE_SIZE * 320) / (disH);
        if (lineH > 320)
        {
            lineH = 320;
        }                     //line height and limit
        int lineOff = (160) - (lineH / 2);  

        printf("LineH: %d\n", lineH);
        printf("LineOff: %d\n", lineOff);
        
        draw_vertical_line(data, begin, end);
        
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

    // walls
    data->walls.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->walls.basic_color = 0x777777;
    data->walls.addr = mlx_get_data_addr(data->walls.img_ptr, &data->walls.bpp,
        &data->walls.line_length, &data->walls.endian);
    draw_square(data->walls, create_trgb(255, 255, 255, 255), HEIGHT, WIDTH);
    draw_ray(data);
    
    // mlx_put_image_to_window(data->mlx, data->win, data->ray.img_ptr, data->minimap_s.position.x, data->minimap_s.position.y);
    mlx_put_image_to_window(data->mlx, data->win, data->walls.img_ptr, 0, 0);
}
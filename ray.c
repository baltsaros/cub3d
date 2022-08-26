/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:09:32 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/26 16:17:14 by mthiry           ###   ########.fr       */
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

void    calculate_ray(t_data *data, t_ray_calcul ray)
{
    t_point begin;
    t_point end;
    float   Tan;

    ray.r = 0;
    ray.ra = FixAng(data->player_s.p_ang + 30);
    while (ray.r < FIELD_OF_VIEW)
    {
        Tan = tan(degToRad(ray.ra));
        ray.dof = 0;
        ray.disV = 100000;
        if (cos(degToRad(ray.ra)) > 0.001)
        {
            ray.rx = (((int)data->player_s.pos_x / 64) * 64) + 64;
            ray.ry = (data->player_s.pos_x - ray.rx) * Tan + data->player_s.pos_y;
            ray.xo = 64;
            ray.yo = -ray.xo * Tan;
        }
        else if (cos(degToRad(ray.ra)) <- 0.001)
        {
            ray.rx = (((int)data->player_s.pos_x / 64) * 64) - 0.0001;
            ray.ry = (data->player_s.pos_x - ray.rx) * Tan + data->player_s.pos_y;
            ray.xo = -64;
            ray.yo = -ray.xo * Tan;
        }
        else
        {
            ray.rx = data->player_s.pos_x;
            ray.ry = data->player_s.pos_y;
            ray.dof = 8;
        }
        while (ray.dof < 8)
        {
            ray.mx = (int)(ray.rx) / 64;
            ray.my = (int)(ray.ry) / 64;            
            if (ray.my >= 0 && ray.mx >= 0 && ray.my < (int)data->map.height && ray.mx < (int)data->map.width - 1 && data->map.map[ray.my][ray.mx] == '1')
            {
                ray.dof = 8;
                ray.disV = cos(degToRad(ray.ra)) * (ray.rx - data->player_s.pos_x) - sin(degToRad(ray.ra)) * (ray.ry - data->player_s.pos_y);
            }         
            else
            {
                ray.rx += ray.xo;
                ray.ry += ray.yo;
                ray.dof++;
            }
        }
        ray.vx = ray.rx;
        ray.vy = ray.ry;
        ray.dof = 0;
        ray.disH = 100000;
        Tan = 1.0 / Tan;
        if (sin(degToRad(ray.ra)) > 0.001)
        {
            ray.ry = (((int)data->player_s.pos_y / 64) * 64) - 0.0001;
            ray.rx = (data->player_s.pos_y - ray.ry) * Tan + data->player_s.pos_x;
            ray.yo = -64;
            ray.xo = -ray.yo * Tan;
        }
        else if (sin(degToRad(ray.ra)) < -0.001)
        {
            ray.ry = (((int)data->player_s.pos_y / 64) * 64) + 64;
            ray.rx = (data->player_s.pos_y - ray.ry) * Tan + data->player_s.pos_x;
            ray.yo = 64;
            ray.xo = -ray.yo * Tan;
        }
        else
        {
            ray.rx = data->player_s.pos_x;
            ray.ry = data->player_s.pos_y;
            ray.dof = 8;
        }
        while (ray.dof < 8)
        {
            ray.mx = ((int)(ray.rx) / 64);
            ray.my = ((int)(ray.ry) / 64);
            if (ray.my >= 0 && ray.mx >= 0 && ray.my < (int)data->map.height && ray.mx < (int)data->map.width - 1 && data->map.map[ray.my][ray.mx] == '1')
            {
                ray.dof = 8;
                ray.disH = cos(degToRad(ray.ra)) * (ray.rx - data->player_s.pos_x) - sin(degToRad(ray.ra)) * (ray.ry - data->player_s.pos_y);
            }
            else
            {
                ray.rx += ray.xo;
                ray.ry += ray.yo;
                ray.dof++;
            }
        }
        if (ray.disV < ray.disH)
        {
            ray.rx = ray.vx;
            ray.ry = ray.vy;
            ray.disH = ray.disV;
        }
        begin.x = data->player_s.pos_x + (PLAYER_SIZE / 2);
        begin.y = data->player_s.pos_y + (PLAYER_SIZE / 2);
        end.x = ray.rx;
        end.y = ray.ry;
        bresenham(data, begin, end, &data->ray);


        printf("Dist: %f\n", ray.disH);

        int ca = FixAng(data->player_s.p_ang - ray.ra);
        ray.disH = ray.disH * cos(degToRad(ca)); 
        int distProj;
        distProj = (WIDTH / 2) / tan(degToRad(FIELD_OF_VIEW / 2));

        printf("distProj: %d\n", distProj);

        int wallHeight;
        wallHeight = (SQUARE_SIZE / ray.disH) * distProj;

        printf("wallHeight: %d\n", wallHeight);
        
        printf("Field of view: %d\n", FIELD_OF_VIEW);

        begin.x = ray.r * (WIDTH / FIELD_OF_VIEW);
        begin.y = (HEIGHT / 2) - (wallHeight / 2);
        end.x = begin.x;
        end.y = begin.y + wallHeight;

        for (int i = 0; i != ((ray.r + 1) * (WIDTH / FIELD_OF_VIEW)); i++)
        {
            draw_vertical_line(data, begin, end);
            begin.x = (ray.r * (WIDTH / FIELD_OF_VIEW)) + i;
            end.x = begin.x;
        }
        
        ray.ra = FixAng(ray.ra - 1);
        ray.r++;
    }
}

void  draw_ray(t_data *data, t_ray_calcul ray)
{
    calculate_ray(data, ray);
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
    draw_ray(data, data->ray_calcul);
    
    mlx_put_image_to_window(data->mlx, data->win, data->ray.img_ptr, data->minimap_s.position.x, data->minimap_s.position.y);
    mlx_put_image_to_window(data->mlx, data->win, data->walls.img_ptr, 0, 0);
}
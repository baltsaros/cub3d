/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:09:32 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/26 16:56:40 by mthiry           ###   ########.fr       */
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
    for (int i = 0; i != ((ray->r + 1) * (WIDTH / FIELD_OF_VIEW)); i++)
    {
        draw_vertical_line(data, begin, end);
        begin.x = (ray->r * (WIDTH / FIELD_OF_VIEW)) + i;
        end.x = begin.x;
    }
}

void    fisheye_fix(t_data *data, t_ray_calcul *ray)
{
    int ca;
    
    ca = FixAng(data->player_s.p_ang - ray->ra);
    ray->disH = ray->disH * cos(degToRad(ca));  
}

void    draw_ray(t_data *data, t_ray_calcul *ray)
{
    t_point begin;
    t_point end;
    
    begin.x = data->player_s.pos_x + (PLAYER_SIZE / 2);
    begin.y = data->player_s.pos_y + (PLAYER_SIZE / 2);
    end.x = ray->rx;
    end.y = ray->ry;
    bresenham(data, begin, end, &data->ray);
}

void   adapt_distance(t_ray_calcul *ray)
{
    if (ray->disV < ray->disH)
    {
        ray->rx = ray->vx;
        ray->ry = ray->vy;
        ray->disH = ray->disV;
    }
}

void    calculate_ray(t_data *data, t_ray_calcul ray)
{
    float Tan;
    
    ray.r = 0;
    ray.ra = FixAng(data->player_s.p_ang + 30);
    while (ray.r < FIELD_OF_VIEW)
    {
        Tan = tan(degToRad(ray.ra));
        check_vertical_wall(data, &ray, Tan);
        ray.vx = ray.rx;
        ray.vy = ray.ry;
        Tan = 1.0 / Tan;
        check_horizontal_wall(data, &ray, Tan);
        adapt_distance(&ray);
        // Next
        draw_ray(data, &ray);
        fisheye_fix(data, &ray);
        init_calculate_wall(data, &ray);
        ray.ra = FixAng(ray.ra - 1);
        ray.r++;
    }
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
    calculate_ray(data, data->ray_calcul);
    
    mlx_put_image_to_window(data->mlx, data->win, data->ray.img_ptr, data->minimap_s.position.x, data->minimap_s.position.y);
    mlx_put_image_to_window(data->mlx, data->win, data->walls.img_ptr, 0, 0);
}
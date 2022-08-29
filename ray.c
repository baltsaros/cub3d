/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:09:32 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/29 15:07:17 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void   adapt_distance(t_ray_calcul *ray)
{
    if (ray->disV < ray->disH)
    {
        ray->rx = ray->vx;
        ray->ry = ray->vy;
        ray->disH = ray->disV;
    }
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

void    fisheye_fix(t_data *data, t_ray_calcul *ray)
{
    int ca;
    
    ca = FixAng(data->player_s.p_ang - ray->ra);
    ray->disH = ray->disH * cos(degToRad(ca));  
}

void    raycast(t_data *data, t_ray_calcul ray)
{
    float Tan;
    
    ray.r = 0;
    ray.ra = FixAng(data->player_s.p_ang + 30);

    // ray.ra = ((float)1 - (WIDTH / 2)) * 33 / (WIDTH / 2);

    while (ray.r < FIELD_OF_VIEW)
    // while (ray.r < WIDTH)
    {
        Tan = tan(degToRad(ray.ra));
        check_vertical_wall(data, &ray, Tan);
        ray.vx = ray.rx;
        ray.vy = ray.ry;
        Tan = 1.0 / Tan;
        check_horizontal_wall(data, &ray, Tan);
        adapt_distance(&ray);
        draw_ray(data, &ray);
        fisheye_fix(data, &ray);

        printf("Distance: %f\n", ray.disH);

        init_calculate_wall(data, &ray);
        ray.ra = FixAng(ray.ra - 1);

        // ray.ra = ((float)ray.r - (WIDTH / 2)) * 33 / (WIDTH / 2);
        
        ray.r++;
        printf("Ray %dth launch\n", ray.r);
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
    init_wall(data);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:09:32 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/08 18:25:42 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int   adapt_distance(t_ray_calcul *ray, int posH, int posV)
{
    if (ray->disV < ray->disH)
    {
        ray->rx = ray->vx;
        ray->ry = ray->vy;
        ray->disH = ray->disV;
        return (posV);
    }
    return (posH);
}

void    fisheye_fix(t_data *data, t_ray_calcul *ray)
{
    float ca;
    
    ca = FixAng(data->player_s.p_ang - ray->ra);
    ray->disH = ray->disH * cos(degToRad(ca));  
}

void    raycast(t_data *data, t_ray_calcul ray)
{
    float   Tan;
    int     posH;
    int     posV;
    int     pos;
    
    ray.r = 0;
    ray.ra = FixAng(data->player_s.p_ang + 30);
    posH = 0;
    posV = 0;
    pos = 0;
    while (ray.r < NB_RAYS)
    {
        Tan = tan(degToRad(ray.ra));
        posV = check_vertical_wall(data, &ray, Tan);
        ray.vx = ray.rx;
        ray.vy = ray.ry;
        Tan = 1.0 / Tan;
        posH = check_horizontal_wall(data, &ray, Tan);
        pos = adapt_distance(&ray, posH, posV);
        fisheye_fix(data, &ray);

        // if (ray.r == NB_RAYS / 2)
        // {
        //     printf("ra: %f\n\n", ray.ra);
        //     printf("pos_x: %f\n", data->player_s.pos_x);
        //     printf("pos_y: %f\n", data->player_s.pos_y);

        //     printf("rx: %f\n", ray.rx);
        //     printf("ry: %f\n", ray.ry);
        //     printf("disH: %f\n", ray.disH);

        //     printf("vx: %f\n", ray.vx);
        //     printf("vy: %f\n", ray.vy);
        //     printf("disV: %f\n", ray.disV);
        //     printf("\n");
        // }

        init_calculate_wall(data, &ray, pos);
        ray.ra = FixAng(ray.ra - ((float)FIELD_OF_VIEW / (float)NB_RAYS));
        ray.r++;
    }
}
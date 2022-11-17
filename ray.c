/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:09:32 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/16 16:27:01 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	adapt_distance(t_ray_calcul *ray, int posH, int posV)
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
	float	ca;
	
	ca = FixAng(data->player_s.p_ang - ray->ra);
	ray->disH = ray->disH * cos(degToRad(ca));  
}

void	raycast(t_data *data, t_ray_calcul ray)
{
    float   Tan;
    int     posH;
    int     posV;
    int     pos;
    
    ray.r = 0;
    ray.ra = FixAng(data->player_s.p_ang + 30);
    while (ray.r < WIDTH)
    {
        Tan = tan(degToRad(ray.ra));
        posV = check_vertical_wall(data, &ray, Tan);
        ray.vx = ray.rx;
        ray.vy = ray.ry;
        posH = check_horizontal_wall(data, &ray, (1.0 / Tan));
        pos = adapt_distance(&ray, posH, posV);
        fisheye_fix(data, &ray);
        init_calculate_wall(data, &ray, pos);
        ray.ra = FixAng(ray.ra - ((float)FIELD_OF_VIEW / (float)WIDTH));
        ray.r++;
    }
}
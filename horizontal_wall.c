/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:36:36 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/26 16:41:43 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    calculate_horizontal_distance(t_data *data, t_ray_calcul *ray, int dof)
{
    while (dof < 8)
    {
        ray->mx = ((int)(ray->rx) / SQUARE_SIZE);
        ray->my = ((int)(ray->ry) / SQUARE_SIZE);
        if (ray->my >= 0 && ray->mx >= 0 && ray->my < (int)data->map.height && ray->mx < (int)data->map.width - 1 && data->map.map[ray->my][ray->mx] == '1')
        {
            dof = 8;
            ray->disH = cos(degToRad(ray->ra)) * (ray->rx - data->player_s.pos_x) - sin(degToRad(ray->ra)) * (ray->ry - data->player_s.pos_y);
        }
        else
        {
            ray->rx += ray->xo;
            ray->ry += ray->yo;
            dof++;
        }
    }
}

void    check_horizontal_wall(t_data *data, t_ray_calcul *ray, float Tan)
{
    int dof;

    dof = 0;
    ray->disH = 100000;
    if (sin(degToRad(ray->ra)) > 0.001)
    {
        ray->ry = (((int)data->player_s.pos_y / SQUARE_SIZE) * SQUARE_SIZE) - 0.0001;
        ray->rx = (data->player_s.pos_y - ray->ry) * Tan + data->player_s.pos_x;
        ray->yo = -SQUARE_SIZE;
        ray->xo = -ray->yo * Tan;
    }
    else if (sin(degToRad(ray->ra)) < -0.001)
    {
        ray->ry = (((int)data->player_s.pos_y / SQUARE_SIZE) * SQUARE_SIZE) + SQUARE_SIZE;
        ray->rx = (data->player_s.pos_y - ray->ry) * Tan + data->player_s.pos_x;
        ray->yo = SQUARE_SIZE;
        ray->xo = -ray->yo * Tan;
    }
    else
    {
        ray->rx = data->player_s.pos_x;
        ray->ry = data->player_s.pos_y;
        dof = 8;
    }
}
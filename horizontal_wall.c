/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:36:36 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/08 18:32:06 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float   disH_calcul(t_data *data, float ra, float ry, float rx)
{
    float   disH;
    float   first;
    float   second;

    first = cos(degToRad(ra)) * (rx - data->player_s.pos_x);
    second = sin(degToRad(ra)) * (ry - data->player_s.pos_y);
    disH = first - second;
    return (disH);
}

void    calculate_horizontal_distance(t_data *data, t_ray_calcul *ray, int dof)
{
    while ((size_t)dof < data->map.height)
    {
        ray->mx = ((int)(ray->rx) / SQUARE_SIZE);
        ray->my = ((int)(ray->ry) / SQUARE_SIZE);
        if (ray->my >= 0 && ray->mx >= 0
            && ray->my < (int)data->map.height
            && ray->mx < (int)data->map.width
            && data->map.map[ray->my][ray->mx] == '1')
        {
            dof = data->map.height;
            ray->disH = disH_calcul(data, ray->ra, ray->ry, ray->rx);
        }
        else
        {
            ray->rx += ray->xo;
            ray->ry += ray->yo;
            dof++;
        }
    }
}

int    check_up(t_data *data, t_ray_calcul *ray, float Tan)
{
    ray->ry = (((int)data->player_s.pos_y / SQUARE_SIZE) * SQUARE_SIZE) - 0.0001;
    ray->rx = (data->player_s.pos_y - ray->ry) * Tan + data->player_s.pos_x;
    ray->yo = -SQUARE_SIZE;
    ray->xo = -ray->yo * Tan;
    return (NORTH);
}

int    check_down(t_data *data, t_ray_calcul *ray, float Tan)
{
    ray->ry = (((int)data->player_s.pos_y / SQUARE_SIZE) * SQUARE_SIZE) + SQUARE_SIZE;
    ray->rx = (data->player_s.pos_y - ray->ry) * Tan + data->player_s.pos_x;
    ray->yo = SQUARE_SIZE;
    ray->xo = -ray->yo * Tan;
    return (SOUTH);
}

int check_horizontal_wall(t_data *data, t_ray_calcul *ray, float Tan)
{
    int dof;
    int ret;

    dof = 0;
    ret = 0;
    ray->disH = 100000;
    if (sin(degToRad(ray->ra)) > 0)
        ret = check_up(data, ray, Tan);
    else if (sin(degToRad(ray->ra)) < -0)
        ret = check_down(data, ray, Tan);
    else
    {
        ray->rx = data->player_s.pos_x;
        ray->ry = data->player_s.pos_y;
        dof = 8;
        ret = ERROR_POS;

        ray->disH = 100;
    }
    calculate_horizontal_distance(data, ray, dof);
    return (ret);
}
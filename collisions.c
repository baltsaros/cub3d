/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:48:39 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/14 18:00:09 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mono_raycast(t_data *data, t_ray_calcul *ray, float angle)
{
    float   Tan;
    int     posH;
    int     posV;
    int     pos;
    
    ray->ra = FixAng(angle);
    posH = 0;
    posV = 0;
    pos = 0;
    Tan = tan(degToRad(ray->ra));
    posV = check_vertical_wall(data, ray, Tan);
    ray->vx = ray->rx;
    ray->vy = ray->ry;
    Tan = 1.0 / Tan;
    posH = check_horizontal_wall(data, ray, Tan);
    pos = adapt_distance(ray, posH, posV);
}

int	hitbox_wall(t_data *data, float angle)
{
    t_ray_calcul mono;

    mono_raycast(data, &mono, angle);
    if (mono.disH < 10)
        return (0);
    return (1);
}
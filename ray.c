/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:09:32 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/27 23:29:01 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	adapt_distance(t_ray_calcul *ray, int posH, int posV)
{
	if (ray->disv < ray->dish)
	{
		ray->rx = ray->vx;
		ray->ry = ray->vy;
		ray->dish = ray->disv;
		ray->is_door_h = ray->is_door_v;
		return (posV);
	}
	return (posH);
}

void	fisheye_fix(t_data *data, t_ray_calcul *ray)
{
	float	ca;

	ca = fixang(data->player_s.p_ang - ray->ra);
	ray->dish = ray->dish * cos(degtorad(ca));
}

void	raycast(t_data *data, t_ray_calcul ray)
{
	float	tan_c;
	int		posh;
	int		posv;
	int		pos;

	ray.r = 0;
	ray.ra = fixang(data->player_s.p_ang + 30);
	while (ray.r < WIDTH)
	{
		ray.is_door_h = 0;
		ray.is_door_v = 0;
		tan_c = tan(degtorad(ray.ra));
		posv = check_vertical_wall(data, &ray, tan_c);
		ray.vx = ray.rx;
		ray.vy = ray.ry;
		posh = check_horizontal_wall(data, &ray, (1.0 / tan_c));
		pos = adapt_distance(&ray, posh, posv);
		fisheye_fix(data, &ray);
		init_calculate_wall(data, &ray, pos);
		data->depth[ray.r] = ray.dish;
		ray.ra = fixang(ray.ra - ((float)FIELD_OF_VIEW / (float)WIDTH));
		ray.r++;
	}
}

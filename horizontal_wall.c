/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:36:36 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/29 15:15:45 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_horizontal_distance(t_data *data, t_ray_calcul *ray,
		int index)
{
	while ((size_t)index < data->map.height)
	{
		ray->mx = ((int)(ray->rx) / SQUARE_SIZE);
		ray->my = ((int)(ray->ry) / SQUARE_SIZE);
		if (is_within_maps(ray->my, ray->mx, data->map.height, data->map.width)
			&& is_wall(data->map.map[ray->my][ray->mx]))
		{
			index = data->map.height;
			ray->dish = dis_calcul(data, ray->ra, ray->ry, ray->rx);
			if (data->map.map[ray->my][ray->mx] == 'D')
				ray->is_door_h = 1;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			index++;
		}
	}
}

int	check_up(t_data *data, t_ray_calcul *ray, float Tan)
{
	ray->ry = (((int)data->player_s.pos_y / SQUARE_SIZE) * SQUARE_SIZE)
		- 0.0005;
	ray->rx = (data->player_s.pos_y - ray->ry) * Tan + data->player_s.pos_x;
	ray->yo = -SQUARE_SIZE;
	ray->xo = -ray->yo * Tan;
	return (NORTH);
}

int	check_down(t_data *data, t_ray_calcul *ray, float Tan)
{
	ray->ry = (((int)data->player_s.pos_y / SQUARE_SIZE) * SQUARE_SIZE)
		+ SQUARE_SIZE;
	ray->rx = (data->player_s.pos_y - ray->ry) * Tan + data->player_s.pos_x;
	ray->yo = SQUARE_SIZE;
	ray->xo = -ray->yo * Tan;
	return (SOUTH);
}

int	check_horizontal_wall(t_data *data, t_ray_calcul *ray, float Tan)
{
	int	index;
	int	ret;

	index = 0;
	ret = 0;
	ray->dish = 100000;
	if (sin(degtorad(ray->ra)) > 0.001)
		ret = check_up(data, ray, Tan);
	else if (sin(degtorad(ray->ra)) < -0.001)
		ret = check_down(data, ray, Tan);
	else
	{
		ray->rx = data->player_s.pos_x;
		ray->ry = data->player_s.pos_y;
		index = (int)data->map.height;
		ret = UNDEFINED;
	}
	calculate_horizontal_distance(data, ray, index);
	return (ret);
}

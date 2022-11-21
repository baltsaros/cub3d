/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:36:36 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/21 16:40:43 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_horizontal_distance(t_data *data, t_ray_calcul *ray, int dof)
{
	while ((size_t)dof < data->map.height)
	{
		ray->mx = ((int)(ray->rx) / SQUARE_SIZE);
		ray->my = ((int)(ray->ry) / SQUARE_SIZE);
		if (ray->my >= 0 && ray->mx >= 0
			&& ray->my < (int)data->map.height
			&& ray->mx < (int)data->map.width
			&& data->map.map[ray->my][ray->mx] != '0'
			&& is_player(data->map.map[ray->my][ray->mx]))
		{
			dof = data->map.height;
			ray->dish = dis_calcul(data, ray->ra, ray->ry, ray->rx);
			if (data->map.map[ray->my][ray->mx] == 'D')
				ray->is_door_h = 1;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			dof++;
		}
	}
}

int	check_up(t_data *data, t_ray_calcul *ray, float Tan)
{
	ray->ry = (((int)data->player_s.pos_y / SQUARE_SIZE) * SQUARE_SIZE)
		- 1;
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
	int	dof;
	int	ret;

	dof = 0;
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
		dof = (int)data->map.height;
		ret = ERROR_POS;
	}
	calculate_horizontal_distance(data, ray, dof);
	return (ret);
}

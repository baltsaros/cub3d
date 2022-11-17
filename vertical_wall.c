/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:35:14 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/17 18:46:12 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	disv_calcul(t_data *data, float ra, float ry, float rx)
{
	float	disv;
	float	first;
	float	second;

	first = cos(degtorad(ra)) * (rx - data->player_s.pos_x);
	second = sin(degtorad(ra)) * (ry - data->player_s.pos_y);
	disv = first - second;
	return (disv);
}

void	calculate_vertical_distance(t_data *data, t_ray_calcul *ray, int dof)
{
	while ((size_t)dof < data->map.width)
	{
		ray->mx = (int)(ray->rx) / SQUARE_SIZE;
		ray->my = (int)(ray->ry) / SQUARE_SIZE;
		if (ray->my >= 0 && ray->mx >= 0
			&& ray->my < (int)data->map.height
			&& ray->mx < (int)data->map.width
			&& data->map.map[ray->my][ray->mx] == '1')
		{
			dof = data->map.width;
			ray->disv = disv_calcul(data, ray->ra, ray->ry, ray->rx);
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			dof++;
		}
	}
}

int	check_right(t_data *data, t_ray_calcul *ray, float Tan)
{
	ray->rx = (((int)data->player_s.pos_x / SQUARE_SIZE) * SQUARE_SIZE)
		+ SQUARE_SIZE;
	ray->ry = (data->player_s.pos_x - ray->rx) * Tan + data->player_s.pos_y;
	ray->xo = SQUARE_SIZE;
	ray->yo = -ray->xo * Tan;
	return (EAST);
}

int	check_left(t_data *data, t_ray_calcul *ray, float Tan)
{
	ray->rx = (((int)data->player_s.pos_x / SQUARE_SIZE) * SQUARE_SIZE)
		- 0.0001;
	ray->ry = (data->player_s.pos_x - ray->rx) * Tan + data->player_s.pos_y;
	ray->xo = -SQUARE_SIZE;
	ray->yo = -ray->xo * Tan;
	return (WEST);
}

int	check_vertical_wall(t_data *data, t_ray_calcul *ray, float Tan)
{
	int	dof;
	int	ret;

	dof = 0;
	ret = 0;
	ray->disv = 100000;
	if (cos(degtorad(ray->ra)) > 0.001)
		ret = check_right(data, ray, Tan);
	else if (cos(degtorad(ray->ra)) < -0.001)
		ret = check_left(data, ray, Tan);
	else
	{
		ray->rx = data->player_s.pos_x;
		ray->ry = data->player_s.pos_y;
		dof = (int)data->map.width;
		ret = ERROR_POS;
	}
	calculate_vertical_distance(data, ray, dof);
	return (ret);
}

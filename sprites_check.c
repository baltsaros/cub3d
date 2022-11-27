/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 20:06:35 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/27 01:57:53 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_sprites(t_data *data, t_ray_calcul *ray, int index)
{
	while ((size_t)index < data->map.height)
	{
		ray->mx = ((int)(ray->rx) / SQUARE_SIZE);
		ray->my = ((int)(ray->ry) / SQUARE_SIZE);
		if (is_within_maps(ray->my, ray->mx, data->map.height, data->map.width)
			&& (is_wall(data->map.map[ray->my][ray->mx])
			|| data->map.map[ray->my][ray->mx] == 'P'))
			index = data->map.height;
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			index++;
		}
	}
}

void	check_up_sprite(t_data *data, t_ray_calcul *ray, t_object *soldier, float Tan)
{
	(void)soldier;
	ray->ry = (((int)data->player_s.pos_y / SQUARE_SIZE) * SQUARE_SIZE)
		- 0.0005;
	ray->rx = (data->player_s.pos_y - ray->ry) * Tan + data->player_s.pos_x;
	ray->yo = -SQUARE_SIZE;
	ray->xo = -ray->yo * Tan;
}

void	check_down_sprite(t_data *data, t_ray_calcul *ray, t_object *soldier, float Tan)
{
	(void)soldier;
	ray->ry = (((int)data->player_s.pos_y / SQUARE_SIZE) * SQUARE_SIZE)
		+ SQUARE_SIZE;
	ray->rx = (data->player_s.pos_y - ray->ry) * Tan + data->player_s.pos_x;
	ray->yo = SQUARE_SIZE;
	ray->xo = -ray->yo * Tan;
}

void	cast_ray_in_dir(t_data *data, t_ray_calcul *ray, t_object *soldier, float Tan)
{
	int	index;

	(void)index;

	index = 0;
	if (sin(degtorad(ray->ra)) > 0.001)
		check_up_sprite(data, ray, soldier, Tan);
	else if (sin(degtorad(ray->ra)) < -0.001)
		check_down_sprite(data, ray, soldier, Tan);
	else
	{
		ray->rx = data->player_s.pos_x;
		ray->ry = data->player_s.pos_y;
		index = (int)data->map.height;
	}
	printf("ry: %f\n", ray->ry);
	printf("rx: %f\n", ray->rx);
	check_sprites(data, ray, index);
}
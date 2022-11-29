/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:15:12 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/29 15:14:05 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_data *data, t_ray_calcul *collisions, double mult)
{
	if (!is_wall(data->map.map
			[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo]))
	{
		data->minimap_s.position.x += data->player_s.delta_x
			* data->minimap_s.step * mult;
		data->player_s.pos_x += data->player_s.speed
			* data->player_s.delta_x * mult;
	}
	if (!is_wall(data->map.map
			[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE]))
	{
		data->minimap_s.position.y += data->player_s.delta_y
			* data->minimap_s.step * mult;
		data->player_s.pos_y += data->player_s.speed
			* data->player_s.delta_y * mult;
	}
}

void	move_down(t_data *data, t_ray_calcul *collisions, double mult)
{
	if (!is_wall(data->map.map
			[collisions->ipy / SQUARE_SIZE][collisions->ipx_sub_xo]))
	{
		data->player_s.pos_x -= data->player_s.speed
			* data->player_s.delta_x * mult;
		data->minimap_s.position.x -= data->player_s.delta_x
			* data->minimap_s.step * mult;
	}
	if (!is_wall(data->map.map
			[collisions->ipy_sub_yo][collisions->ipx / SQUARE_SIZE]))
	{
		data->player_s.pos_y -= data->player_s.speed
			* data->player_s.delta_y * mult;
		data->minimap_s.position.y -= data->player_s.delta_y
			* data->minimap_s.step * mult;
	}
}

void	move_right(t_data *data, t_ray_calcul *collisions, double mult)
{
	if (!is_wall(data->map.map
			[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo]))
	{
		data->player_s.pos_x -= data->player_s.speed
			* data->player_s.delta_y * mult;
		data->minimap_s.position.x -= data->player_s.delta_y
			* data->minimap_s.step * mult;
	}
	if (!is_wall(data->map.map
			[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE]))
	{
		data->player_s.pos_y -= data->player_s.speed
			* -data->player_s.delta_x * mult;
		data->minimap_s.position.y -= -data->player_s.delta_x
			* data->minimap_s.step * mult;
	}
}

void	move_left(t_data *data, t_ray_calcul *collisions, double mult)
{
	if (!is_wall(data->map.map
			[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo]))
	{
		data->player_s.pos_x -= data->player_s.speed
			* -data->player_s.delta_y * mult;
		data->minimap_s.position.x -= -data->player_s.delta_y
			* data->minimap_s.step * mult;
	}
	if (!is_wall(data->map.map
			[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE]))
	{
		data->player_s.pos_y -= data->player_s.speed
			* data->player_s.delta_x * mult;
		data->minimap_s.position.y -= data->player_s.delta_x
			* data->minimap_s.step * mult;
	}
}

void	move(t_data *data)
{
	t_ray_calcul	collisions;

	if (data->keyboard.w ^ data->keyboard.s)
	{
		collisions_calculs_up_down(data, &collisions);
		if (data->keyboard.w)
			move_up(data, &collisions, set_mult(data, 0));
		if (data->keyboard.s)
			move_down(data, &collisions, set_mult(data, 0));
	}
	if (data->keyboard.d
		&& !data->keyboard.a)
	{
		collisions_calculs_right(data, &collisions);
		move_right(data, &collisions, set_mult(data, 1));
	}
	else if (data->keyboard.a
		&& !data->keyboard.d)
	{
		collisions_calculs_left(data, &collisions);
		move_left(data, &collisions, set_mult(data, 1));
	}
}

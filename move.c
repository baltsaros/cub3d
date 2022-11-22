/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:15:12 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/22 14:12:36 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_data *data, t_ray_calcul *collisions)
{
	if (data->map.map
		[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo] == '0'
		|| data->map.map
		[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo] == 'C'
			|| !is_player(data->map.map
			[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo]))
	{
		data->minimap_s.position.x += data->player_s.delta_x
			* data->minimap_s.step;
		data->player_s.pos_x += data->player_s.speed
			* data->player_s.delta_x;
	}
	if (data->map.map
		[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE] == '0'
		|| data->map.map
		[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE] == 'C'
			|| !is_player(data->map.map
			[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE]))
	{
		data->minimap_s.position.y += data->player_s.delta_y
			* data->minimap_s.step;
		data->player_s.pos_y += data->player_s.speed
			* data->player_s.delta_y;
	}
}

void	move_down(t_data *data, t_ray_calcul *collisions)
{
	if (data->map.map
		[collisions->ipy / SQUARE_SIZE][collisions->ipx_sub_xo] == '0'
		|| data->map.map
		[collisions->ipy / SQUARE_SIZE][collisions->ipx_sub_xo] == 'C'
			|| !is_player(data->map.map
			[collisions->ipy / SQUARE_SIZE][collisions->ipx_sub_xo]))
	{
		data->player_s.pos_x -= data->player_s.speed
			* data->player_s.delta_x;
		data->minimap_s.position.x -= data->player_s.delta_x
			* data->minimap_s.step;
	}
	if (data->map.map
		[collisions->ipy_sub_yo][collisions->ipx / SQUARE_SIZE] == '0'
		|| data->map.map
		[collisions->ipy_sub_yo][collisions->ipx / SQUARE_SIZE] == 'C'
			|| !is_player(data->map.map
			[collisions->ipy_sub_yo][collisions->ipx / SQUARE_SIZE]))
	{
		data->player_s.pos_y -= data->player_s.speed
			* data->player_s.delta_y;
		data->minimap_s.position.y -= data->player_s.delta_y
			* data->minimap_s.step;
	}
}

void	move_right(t_data *data, t_ray_calcul *collisions)
{
	if (data->map.map
		[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo] == '0'
		|| data->map.map
		[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo] == 'C'
			|| !is_player(data->map.map
			[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo]))
	{
		data->player_s.pos_x -= data->player_s.speed
			* data->player_s.delta_y;
		data->minimap_s.position.x -= data->player_s.delta_y
			* data->minimap_s.step;
	}
	if (data->map.map
		[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE] == '0'
		|| data->map.map
		[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE] == 'C'
			|| !is_player(data->map.map
			[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE]))
	{
		data->player_s.pos_y -= data->player_s.speed
			* -data->player_s.delta_x;
		data->minimap_s.position.y -= -data->player_s.delta_x
			* data->minimap_s.step;
	}
}

void	move_left(t_data *data, t_ray_calcul *collisions)
{
	if (data->map.map
		[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo] == '0'
		|| data->map.map
		[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo] == 'C'
			|| !is_player(data->map.map
			[collisions->ipy / SQUARE_SIZE][collisions->ipx_add_xo]))
	{
		data->player_s.pos_x -= data->player_s.speed
			* -data->player_s.delta_y;
		data->minimap_s.position.x -= -data->player_s.delta_y
			* data->minimap_s.step;
	}
	if (data->map.map
		[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE] == '0'
		|| data->map.map
		[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE] == 'C'
			|| !is_player(data->map.map
			[collisions->ipy_add_yo][collisions->ipx / SQUARE_SIZE]))
	{
		data->player_s.pos_y -= data->player_s.speed
			* data->player_s.delta_x;
		data->minimap_s.position.y -= data->player_s.delta_x
			* data->minimap_s.step;
	}
}

void	move(t_data *data)
{
	t_ray_calcul	collisions;

	if (data->keyboard.w ^ data->keyboard.s)
	{
		collisions_calculs_up_down(data, &collisions);
		if (data->keyboard.w && !data->keyboard.d && !data->keyboard.a)
			move_up(data, &collisions);
		if (data->keyboard.s && !data->keyboard.d && !data->keyboard.a)
			move_down(data, &collisions);
	}
	if (data->keyboard.d
		&& !data->keyboard.a
		&& !data->keyboard.w && !data->keyboard.s)
	{
		collisions_calculs_right(data, &collisions);
		move_right(data, &collisions);
	}
	else if (data->keyboard.a
		&& !data->keyboard.d
		&& !data->keyboard.w && !data->keyboard.s)
	{
		collisions_calculs_left(data, &collisions);
		move_left(data, &collisions);
	}
}

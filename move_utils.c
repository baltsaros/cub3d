/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:57:43 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/26 13:14:13 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	collisions_calculs_up_down(t_data *data, t_ray_calcul *collisions)
{
	int	xo;
	int	yo;

	xo = 0;
	yo = 0;
	if (data->player_s.delta_x < 0)
		xo = -(SQUARE_SIZE / 2);
	else
		xo = (SQUARE_SIZE / 2);
	if (data->player_s.delta_y < 0)
		yo = -(SQUARE_SIZE / 2);
	else
		yo = (SQUARE_SIZE / 2);
	collisions->ipx = data->player_s.pos_x;
	collisions->ipx_add_xo = (collisions->ipx + xo) / SQUARE_SIZE;
	collisions->ipx_sub_xo = (collisions->ipx - xo) / SQUARE_SIZE;
	collisions->ipy = data->player_s.pos_y;
	collisions->ipy_add_yo = (collisions->ipy + yo) / SQUARE_SIZE;
	collisions->ipy_sub_yo = (collisions->ipy - yo) / SQUARE_SIZE;
}

void	collisions_calculs_right(t_data *data, t_ray_calcul *collisions)
{
	int	xo;
	int	yo;

	xo = 0;
	yo = 0;
	if (-data->player_s.delta_y < 0)
		xo = -(SQUARE_SIZE / 2);
	else
		xo = (SQUARE_SIZE / 2);
	if (data->player_s.delta_x < 0)
		yo = -(SQUARE_SIZE / 2);
	else
		yo = (SQUARE_SIZE / 2);
	collisions->ipx = data->player_s.pos_x;
	collisions->ipx_add_xo = (collisions->ipx + xo) / SQUARE_SIZE;
	collisions->ipy = data->player_s.pos_y;
	collisions->ipy_add_yo = (collisions->ipy + yo) / SQUARE_SIZE;
}

void	collisions_calculs_left(t_data *data, t_ray_calcul *collisions)
{
	int	xo;
	int	yo;

	xo = 0;
	yo = 0;
	if (data->player_s.delta_y < 0)
		xo = -(SQUARE_SIZE / 2);
	else
		xo = (SQUARE_SIZE / 2);
	if (-data->player_s.delta_x < 0)
		yo = -(SQUARE_SIZE / 2);
	else
		yo = (SQUARE_SIZE / 2);
	collisions->ipx = data->player_s.pos_x;
	collisions->ipx_add_xo = (collisions->ipx + xo) / SQUARE_SIZE;
	collisions->ipy = data->player_s.pos_y;
	collisions->ipy_add_yo = (collisions->ipy + yo) / SQUARE_SIZE;
}

double	set_mult(t_data *data, int dir)
{
	if (dir == 0)
	{
		if (data->keyboard.a || data->keyboard.d)
			return (sqrt(2) / 2);
		else
			return (1.0);
	}
	else
	{
		if (data->keyboard.w || data->keyboard.s)
			return (sqrt(2) / 2);
		else
			return (1.0);
	}
}

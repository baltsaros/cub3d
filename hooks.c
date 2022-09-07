/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:55:14 by abuzdin           #+#    #+#             */
/*   Updated: 2022/09/07 12:34:08 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_input *data, char **map, float x, float y)
{
	int	rx;
	int	ry;

	// printf("py is %f\n", data->py);
	ry = y / data->sy;
	rx = x / data->sx;
	// printf("rx is %d, ry is %d\n", rx, ry);
	// printf("map[%d][%d] is %c\n", ry, rx, map[ry][rx]);
	// printf("px is %f, py is %f\n", data->px, data->py);
	if (map[ry][rx] && map[ry][rx] != '1')
		return (1);
	return (0);
}

int	key_hook(int keycode, t_input *data)
{
	float	step;
	float	turn;

	step = 7;
	turn = 0.2;
	// is_wall(data, data->map.map);
	if (keycode == 53)
	{
		mlx_destroy_image(data->mlx, data->img.mlx_img);
		mlx_destroy_image(data->mlx, data->pl.mlx_img);
		// mlx_destroy_image(data->mlx, data->ray.mlx_img);
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
		cub_free_all(data);
		exit(EXIT_SUCCESS);
	}
	// else if (keycode == 119 && map[y - 1][x] && map[y - 1][x] != '1')
	else if (keycode == 13)
	{
		data->px += step * data->pdx;
		data->py += step * data->pdy;
		// data->px += data->pdx;
		// data->py += data->pdy;
		if (!is_wall(data, data->map.map, data->px, data->py))
		{
			data->px -= step * data->pdx;
			data->py -= step * data->pdy;
		}
	}
	else if (keycode == 1)
	{
		data->px -= step * data->pdx;
		data->py -= step * data->pdy;
		// data->px -= data->pdx;
		// data->py -= data->pdy;
		if (!is_wall(data, data->map.map, data->px, data->py))
		{
			data->px += step * data->pdx;
			data->py += step * data->pdy;
		}
	}
	else if (keycode == 0)
	{
		data->px += step * cos(data->pa - ((90 * PI) / 180));
		data->py += step * sin(data->pa - ((90 * PI) / 180));
		if (!is_wall(data, data->map.map, data->px, data->py))
		{
			data->px -= step * cos(data->pa - ((90 * PI) / 180));
			data->py -= step * sin(data->pa - ((90 * PI) / 180));
		}
	}
	else if (keycode == 2)
	{
		data->px -= step * cos(data->pa - ((90 * PI) / 180));
		data->py -= step * sin(data->pa - ((90 * PI) / 180));
		if (!is_wall(data, data->map.map, data->px, data->py))
		{
			data->px += step * cos(data->pa - ((90 * PI) / 180));
			data->py += step * sin(data->pa - ((90 * PI) / 180));
		}
	}
	else if (keycode == 123)
	{
		data->pa -= turn;
		if (data->pa < 0)
			data->pa += 2 * PI;
		data->pdx = cos(data->pa);
		data->pdy = sin(data->pa);
		data->ra -= turn;
		if (data->ra < 0)
			data->ra += 2 * PI;
		data->rdx = cos(data->ra);
		data->rdy = sin(data->ra);
		data->la -= turn;
		if (data->la < 0)
			data->la += 2 * PI;
		data->ldx = cos(data->la);
		data->ldy = sin(data->la);
		// printf("pa is %f\npdx is %f\npdy is %f\n", data->pa, data->pdx, data->pdy);
	}
	else if (keycode == 124)
	{
		data->pa += turn;
		if (data->pa > 2 * PI)
			data->pa -= 2 * PI;
		data->pdx = cos(data->pa);
		data->pdy = sin(data->pa);
		data->ra += turn;
		if (data->ra > 2 * PI)
			data->ra -= 2 * PI;
		data->rdx = cos(data->ra);
		data->rdy = sin(data->ra);
		data->la += turn;
		if (data->la > 2 * PI)
			data->la -= 2 * PI;
		data->ldx = cos(data->la);
		data->ldy = sin(data->la);
		// printf("pa is %f\npdx is %f\npdy is %f\n", data->pa, data->pdx, data->pdy);
	}
	else
		printf("Key %d was pressed!\n", keycode);
	// render_player(data, &data->pl);
	// printf("pa is %f\npdx is %f\npdy is %f\n", data->pa, data->pdx, data->pdy);
	render(data);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_input *data)
{
	float	px;
	float	py;
	float	xx;
	float	yy;
	float	up;
	float	dw;
	float	mul;
	if (keycode == 1)
	{
		px = data->px;
		py = data->py;
		xx = (float)x - data->px;
		yy = data->py - (float)y;
		up = px * xx + py * yy;
		dw = sqrtf(px * px + py * py) * sqrtf(xx * xx + yy * yy);
		printf("%f, sqrt is %f\n", px * px + py * py, sqrtf(px * px + py * py));
		printf("%f, sqrt is %f\n", xx * xx + yy * yy, sqrtf(xx * xx + yy * yy));
		mul = up / dw;
		printf("up is %f, down is %f, mul is %f\n", up, dw, mul);
		data->pa = acosf(mul);
		if (yy > 0)
			data->pa = 2*PI - data->pa;
		data->la = data->pa - (30 * PI) / 180;
		printf("xx is %f, yy is %f, key is %d\n", xx, yy, keycode);
		// printf("30%% is %f, la is %f\n", (30 * PI) / 180, data->la);
		// data->pdx = cos(data->pa);
		// data->pdy = sin(data->pa);
		printf("px is %f, py is %f, pa is %f\n", px, py, data->pa);
		// printf("pdx: %f, pdy: %f\n", data->pdx, data->pdy);
	}
	render(data);
	return (0);
}

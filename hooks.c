/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:55:14 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/26 11:27:16 by abuzdin          ###   ########.fr       */
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

	step = 5;
	turn = 0.2;
	// is_wall(data, data->map.map);
	if (keycode == 65307)
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
	else if (keycode == 119)
	{
		data->py -= step;
		if (!is_wall(data, data->map.map, data->px, data->py))
			data->py += step;
	}
	else if (keycode == 115)
	{
		data->py += step;
		if (!is_wall(data, data->map.map, data->px, data->py))
			data->py -= step;
	}
	else if (keycode == 97)
	{
		data->px -= step;
		if (!is_wall(data, data->map.map, data->px, data->py))
			data->px += step;
	}
	else if (keycode == 100)
	{
		data->px += step;
		if (!is_wall(data, data->map.map, data->px, data->py))
			data->px -= step;
	}
	else if (keycode == 65361)
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
	else if (keycode == 65363)
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
	render(data);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_input *data)
{
	(void)x;
	(void)y;
	(void)keycode;
	(void)data;
	// cub_free_all(data);
	// if (keycode == 4)
	// 	data->set.zoom *= 1.1;
	// else if (keycode == 5)
	// 	data->set.zoom *= 0.9;
	// data->set.move_x = (x - WIDTH / 2) / (data->set.zoom * WIDTH)
	// 	+ data->set.move_x;
	// data->set.move_y = (y - HEIGHT / 2) / (data->set.zoom * HEIGHT)
	// 	+ data->set.move_y;
	render_player(data, &data->pl);
	return (0);
}

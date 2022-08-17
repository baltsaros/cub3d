/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:55:14 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/17 11:44:19 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	infinite_hook(int keycode, t_data *data)
{
	(void)keycode;
	(void)data;
	// mlx_clear_window(data->mlx, data->win);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_image(data->mlx, data->img.img_ptr);
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
		// cub_free_all(data);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 13)
	{
		data->pos_y -= 5;
		if (data->pos_y < 0)
			data->pos_y = 0;
	}
	else if (keycode == 1)
	{
		data->pos_y += 5;
		if (data->pos_y > HEIGHT)
			data->pos_y = HEIGHT;
	}
	else if (keycode == 0)
	{
		data->pos_x -= 5;
		if (data->pos_y < 0)
			data->pos_y = 0;
	}
	else if (keycode == 2)
	{
		data->pos_x += 5;
		if (data->pos_y > WIDTH)
			data->pos_y = WIDTH;
	}
	// else if (keycode == 65361)
	// 	data->set.move_x *= 1.1;
	// else if (keycode == 65363)
	// 	data->set.move_x *= 0.9;
	// else if (keycode == 65362)
	// 	data->set.move_y *= 1.1;
	// else if (keycode == 65364)
	// 	data->set.move_y *= 0.9;
	// else if (keycode == 45)
	// 	data->set.zoom *= 1.5;
	// else if (keycode == 61)
	// 	data->set.zoom *= 0.9;
	else
		printf("Key %d was pressed!\n", keycode);
	// render(data);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_data *data)
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
	// render(data);
	return (0);
}

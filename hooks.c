/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:55:14 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/21 15:40:54 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, t_input *data)
{
	int		x;
	int		y;
	char	**map;

	x = data->map.player[0];
	y = data->map.player[1];
	map = data->map.map;
	if (keycode == 65307)
	{
		mlx_destroy_image(data->mlx, data->img.mlx_img);
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
		cub_free_all(data);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == 119 && map[y - 1][x] && map[y - 1][x] == '0')
		data->map.player[1] -= 1;
	else if (keycode == 115 && map[y + 1][x] && map[y + 1][x] == '0')
		data->map.player[1] += 1;
	else if (keycode == 97 && map[y][x - 1] && map[y][x - 1] == '0')
		data->map.player[0] -= 1;
	else if (keycode == 100 && map[y][x + 1] && map[y][x + 1] == '0')
		data->map.player[0] += 1;
	else
		printf("Key %d was pressed!\n", keycode);
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
	render(data);
	return (0);
}

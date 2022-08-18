/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:55:14 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/18 14:53:45 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	infinite_hook(int keycode, t_data *data)
{
	(void)keycode;
	(void)data;
	// Temporary solution
	return (0);
}

void	leave(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	// cub_free_all(data);
	exit(EXIT_SUCCESS);
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

void	move(int keycode, t_data *data)
{
	if (keycode == 13)
	{
		data->player_s.pos_win_y -= 5;
		if (data->player_s.pos_win_y < 0)
			data->player_s.pos_win_y = 0;
	}
	else if (keycode == 1)
	{
		data->player_s.pos_win_y += 5;
		if (data->player_s.pos_win_y > HEIGHT - data->size_player)
			data->player_s.pos_win_y = HEIGHT - data->size_player;
	}
	else if (keycode == 0)
	{
		data->player_s.pos_win_x -= 5;
		if (data->player_s.pos_win_x < 0)
			data->player_s.pos_win_x = 0;
	}
	else if (keycode == 2)
	{
		data->player_s.pos_win_x += 5;
		if (data->player_s.pos_win_x > WIDTH - data->size_player)
			data->player_s.pos_win_x = WIDTH - data->size_player;
	}
	// Temporary solution
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	mlx_destroy_image(data->mlx, data->minimap.img_ptr);
	mlx_destroy_image(data->mlx, data->player.img_ptr);
	mlx_clear_window(data->mlx, data->win);
	data->img.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    if (data->img.img_ptr != NULL)
        init_background(data);
	data->minimap.img_ptr = mlx_new_image(data->mlx, data->map.width * data->size_square, data->map.height * data->size_square);
    if (data->minimap.img_ptr != NULL)
	{
		int color;

    	color = 0x000000;
    	data->minimap.addr = mlx_get_data_addr(data->minimap.img_ptr, &data->minimap.bpp,
        	&data->minimap.line_length, &data->minimap.endian);
    	draw_square(data->minimap, data->img.basic_color, data->map.height * data->size_square, data->map.width * data->size_square);
		redraw_map(data, color, data->map.height, data->map.width);
    	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img_ptr, data->pos_x_minimap, data->pos_y_minimap);
	}
	data->player.img_ptr = mlx_new_image(data->mlx, data->size_player, data->size_player);
    if (data->player.img_ptr != NULL)
	{
		data->player.basic_color = 0x0FAE2;
    	data->player.addr = mlx_get_data_addr(data->player.img_ptr, &data->player.bpp,
			&data->player.line_length, &data->player.endian);
    	draw_square(data->player, data->player.basic_color, data->size_player, data->size_player);
    	mlx_put_image_to_window(data->mlx, data->win, data->player.img_ptr, data->player_s.pos_win_x, data->player_s.pos_win_y);
	}
}

int	key_hook_manager(int keycode, t_data *data)
{
	if (keycode == 53)
		leave(data);
	else if (keycode == 0 || keycode == 1 || keycode == 2 || keycode == 13)
		move(keycode, data);
	else
		printf("Key %d was pressed!\n", keycode);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:55:14 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/22 16:43:36 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_data *data)
{
	// Temporary solution
	mlx_destroy_image(data->mlx, data->ceiling.img_ptr);
	mlx_destroy_image(data->mlx, data->minimap.img_ptr);
	mlx_destroy_image(data->mlx, data->player.img_ptr);
	mlx_destroy_image(data->mlx, data->ray.img_ptr);
	mlx_clear_window(data->mlx, data->win);
	data->ceiling.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    if (data->ceiling.img_ptr != NULL)
        init_ceiling(data);
	data->minimap.img_ptr = mlx_new_image(data->mlx, data->minimap_s.width, data->minimap_s.height);
	if (data->minimap.img_ptr != NULL)
	{
		data->minimap.basic_color = 0x000000;
    	data->minimap.addr = mlx_get_data_addr(data->minimap.img_ptr, &data->minimap.bpp,
        	&data->minimap.line_length, &data->minimap.endian);
   		draw_square(data->minimap, create_trgb(255, 255, 255, 255), data->minimap_s.height, data->minimap_s.width);
    	redraw_map(data, data->minimap.basic_color, data->map.height, data->map.width);
    	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img_ptr, data->minimap_s.position.x, data->minimap_s.position.y);
	}
	data->player.img_ptr = mlx_new_image(data->mlx, PLAYER_SIZE, PLAYER_SIZE);
	if (data->player.img_ptr != NULL)
	{
		data->player.basic_color = 0x0FAE2;
    	data->player.addr = mlx_get_data_addr(data->player.img_ptr, &data->player.bpp,
			&data->player.line_length, &data->player.endian);
    	draw_square(data->player, data->player.basic_color, PLAYER_SIZE, PLAYER_SIZE);
		mlx_put_image_to_window(data->mlx, data->win, data->player.img_ptr, data->player_s.pos_win_x, data->player_s.pos_win_y);
	}
    init_ray(data);
}

int	infinite_hook(int keycode, t_data *data)
{
	(void)keycode;
	(void)data;
	// Temporary solution
	return (0);
}

void	leave(t_data *data)
{
	mlx_destroy_image(data->mlx, data->ceiling.img_ptr);
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
		printf("Before data->player_s.y: %f\n", data->player_s.pos_win_y);
		data->player_s.pos_win_y -= 5;
		data->player_s.pos_y -= 5;
		if (data->player_s.pos_win_y < 0)
			data->player_s.pos_win_y = 0;
		printf("Data->player_s.y: %f\n", data->player_s.pos_win_y);
	}
	else if (keycode == 1)
	{
		printf("Before data->player_s.y: %f\n", data->player_s.pos_win_y);
		data->player_s.pos_win_y += 5;
		data->player_s.pos_y += 5;
		if (data->player_s.pos_win_y > HEIGHT - PLAYER_SIZE)
			data->player_s.pos_win_y = HEIGHT - PLAYER_SIZE;
		printf("Data->player_s.y: %f\n", data->player_s.pos_win_y);
	}
	else if (keycode == 0)
	{
		printf("Before data->player_s.x: %f\n", data->player_s.pos_win_x);
		data->player_s.pos_win_x -= 5;
		data->player_s.pos_x -= 5;
		if (data->player_s.pos_win_x < 0)
			data->player_s.pos_win_x = 0;
		printf("Data->player_s.x: %f\n", data->player_s.pos_win_x);
	}
	else if (keycode == 2)
	{
		printf("Before data->player_s.x: %f\n", data->player_s.pos_win_x);
		data->player_s.pos_win_x += 5;
		data->player_s.pos_x += 5;
		if (data->player_s.pos_win_x > WIDTH - PLAYER_SIZE)
			data->player_s.pos_win_x = WIDTH - PLAYER_SIZE;
		printf("Data->player_s.x: %f\n", data->player_s.pos_win_x);
	}
	render(data);
}

void	rotate_fov(int keycode, t_data *data)
{
	if (keycode == 123)
	{
		data->player_s.p_ang += 5;
		data->player_s.delta_x = cos(data->player_s.p_ang) * 5;
		data->player_s.delta_y = -sin(data->player_s.p_ang) * 5;
	}
	else if (keycode == 124)
	{
		data->player_s.p_ang -= 5;
		data->player_s.delta_x = cos(data->player_s.p_ang) * 5;
		data->player_s.delta_y = -sin(data->player_s.p_ang) * 5;
	}
	render(data);
}

int	key_hook_manager(int keycode, t_data *data)
{
	if (keycode == 53)
		leave(data);
	else if (keycode == 0 || keycode == 1 || keycode == 2 || keycode == 13)
		move(keycode, data);
	else if (keycode == 123 || keycode == 124)
		rotate_fov(keycode, data);
	else
		printf("Key %d was pressed!\n", keycode);
	return (0);
}

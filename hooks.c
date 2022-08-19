/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:55:14 by abuzdin           #+#    #+#             */
/*   Updated: 2022/08/19 17:49:28 by mthiry           ###   ########.fr       */
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
		data->player_s.pos_win_y -= 5;
		data->player_s.pos_y -= 5;
		// if (!is_not_in_wall(data))
		// 	printf("Walled\n");
		if (data->player_s.pos_win_y < 0)
			data->player_s.pos_win_y = 0;
	}
	else if (keycode == 1)
	{
		data->player_s.pos_win_y += 5;
		data->player_s.pos_y += 5;
		// if (!is_not_in_wall(data))
		// 	printf("Walled\n");
		if (data->player_s.pos_win_y > HEIGHT - data->size_player)
			data->player_s.pos_win_y = HEIGHT - data->size_player;
	}
	else if (keycode == 0)
	{
		data->player_s.pos_win_x -= 5;
		data->player_s.pos_x -= 5;
		// if (!is_not_in_wall(data))
		// 	printf("Walled\n");
		if (data->player_s.pos_win_x < 0)
			data->player_s.pos_win_x = 0;
	}
	else if (keycode == 2)
	{
		data->player_s.pos_win_x += 5;
		data->player_s.pos_x += 5;
		// if (!is_not_in_wall(data))
		// 	printf("Walled\n");
		if (data->player_s.pos_win_x > WIDTH - data->size_player)
			data->player_s.pos_win_x = WIDTH - data->size_player;
	}
	// render(data);
}

void	rotate_fov(int keycode, t_data *data)
{
	if (keycode == 123)
	{
		data->player_s.p_ang += 5;
		data->player_s.delta_x = cos(degToRad(data->player_s.p_ang));
		data->player_s.delta_y = -sin(degToRad(data->player_s.p_ang));
	}
	else if (keycode == 124)
	{
		data->player_s.p_ang -= 5;
		data->player_s.delta_x = cos(degToRad(data->player_s.p_ang));
		data->player_s.delta_y = -sin(degToRad(data->player_s.p_ang));
	}
	// render(data);
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

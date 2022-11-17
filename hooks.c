/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:55:14 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/17 11:57:58 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == W)
		data->keyboard.w = 1;
	if (keycode == A)
		data->keyboard.a = 1;
	if (keycode == S)
		data->keyboard.s = 1;
	if (keycode == D)
		data->keyboard.d = 1;
	if (keycode == ESC)
		leave(data);
	if (keycode == RIGHT)
		data->keyboard.right = 1;
	if (keycode == LEFT)
		data->keyboard.left = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->keyboard.w = 0;
	if (keycode == A)
		data->keyboard.a = 0;
	if (keycode == S)
		data->keyboard.s = 0;
	if (keycode == D)
		data->keyboard.d = 0;
	if (keycode == RIGHT)
		data->keyboard.right = 0;
	if (keycode == LEFT)
		data->keyboard.left = 0;
	return (0);
}

void	leave(t_data *data)
{
	// mlx_destroy_image(data->mlx, data->ceiling.img_ptr);
	mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	// cub_free_all(data);
	exit(EXIT_SUCCESS);
}

void	rotate_fov(int keycode, t_data *data)
{
	if (keycode == RIGHT)
	{
		data->player_s.p_ang += data->player_s.rot_speed;
		data->player_s.p_ang = FixAng(data->player_s.p_ang);
		data->player_s.delta_x = cos(degToRad(data->player_s.p_ang));
		data->player_s.delta_y = -sin(degToRad(data->player_s.p_ang));
	}
	if (keycode == LEFT)
	{
		data->player_s.p_ang -= data->player_s.rot_speed;
		data->player_s.p_ang = FixAng(data->player_s.p_ang);
		data->player_s.delta_x = cos(degToRad(data->player_s.p_ang));
		data->player_s.delta_y = -sin(degToRad(data->player_s.p_ang));
	}
}

int	mouse_hook(int x, int y, t_data *data)
{
	// printf("dx: %d\nx: %d, y: %d\n", data->x, x, y);
	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return (0);
	if (WIDTH - x > data->x)
	{
		rotate_fov(RIGHT, data);
		data->x += 15;
	}
	else
	{
		rotate_fov(LEFT, data);
		data->x -= 15;
	}
	return (0);
}

int	key_hook_manager(t_data *data)
{
	if (data->keyboard.w || data->keyboard.a
			|| data->keyboard.s || data->keyboard.d)
		move(data);
	if (data->keyboard.right)
		rotate_fov(RIGHT, data);
	if (data->keyboard.left)
		rotate_fov(LEFT, data);
	draw_all(data);
	return (0);
}

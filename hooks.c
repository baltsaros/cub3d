/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:55:14 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/25 15:25:14 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		leave(data, EXIT_SUCCESS);
	if (keycode == W)
		data->keyboard.w = 1;
	if (keycode == A)
		data->keyboard.a = 1;
	if (keycode == S)
		data->keyboard.s = 1;
	if (keycode == D)
		data->keyboard.d = 1;
	if (keycode == RIGHT)
		data->keyboard.right = 1;
	if (keycode == LEFT)
		data->keyboard.left = 1;
	if (keycode == SPACE)
		open_close_door(data, data->ray_calcul);
	if (keycode == SHIFT)
		data->keyboard.shift = 1;
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
	if (keycode == SHIFT)
		data->keyboard.shift = 0;
	return (0);
}

void	rotate_fov(int keycode, t_data *data)
{
	if (keycode == RIGHT)
	{
		data->player_s.p_ang += data->player_s.rot_speed;
		data->player_s.p_ang = fixang(data->player_s.p_ang);
		data->player_s.delta_x = cos(degtorad(data->player_s.p_ang));
		data->player_s.delta_y = -sin(degtorad(data->player_s.p_ang));
	}
	if (keycode == LEFT)
	{
		data->player_s.p_ang -= data->player_s.rot_speed;
		data->player_s.p_ang = fixang(data->player_s.p_ang);
		data->player_s.delta_x = cos(degtorad(data->player_s.p_ang));
		data->player_s.delta_y = -sin(degtorad(data->player_s.p_ang));
	}
}

int	mouse_hook(int x, int y, t_data *data)
{
	if (data->keyboard.shift)
	{
		mlx_mouse_show();
		return (0);
	}
	mlx_mouse_hide();
	mlx_mouse_move(data->win, WIDTH / 2, HEIGHT / 2);
	if (y != HEIGHT / 2)
		y = HEIGHT / 2;
	if (x > (WIDTH / 2) + 15 || x < (WIDTH / 2) - 15)
	{
		if (x > WIDTH / 2)
			data->player_s.p_ang -= data->player_s.rot_speed * 1.5;
		else if (x < WIDTH / 2)
			data->player_s.p_ang += data->player_s.rot_speed * 1.5;
	}
	else
		return (0);
	data->player_s.p_ang = fixang(data->player_s.p_ang);
	data->player_s.delta_x = cos(degtorad(data->player_s.p_ang));
	data->player_s.delta_y = -sin(degtorad(data->player_s.p_ang));
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

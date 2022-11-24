/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:55:14 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/24 08:53:00 by abuzdin          ###   ########.fr       */
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
	int	dif;

	printf("data->x: %d, x: %d\n", data->x, x);
	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return (0);
	if (!data->old_x)
		data->old_x = x;
	dif = abs(data->old_x - x);
	if (WIDTH - x > data->x && dif > 5)
	{
		data->old_x = x;
		rotate_fov(RIGHT, data);
		data->x += 5;
	}
	else if (dif > 5)
	{
		data->old_x = x;
		rotate_fov(LEFT, data);
		data->x -= 5;
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

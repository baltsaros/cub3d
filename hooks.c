/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:55:14 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/15 13:23:33 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESCAPE)
		data->keyboard.esc = 1;
	else if (keycode == W_KEY)
		data->keyboard.w = 1;
	else if (keycode == A_KEY)
		data->keyboard.a = 1;
	else if (keycode == S_KEY)
		data->keyboard.s = 1;
	else if (keycode == D_KEY)
		data->keyboard.d = 1;
	else if (keycode == RIGHT)
		data->keyboard.right = 1;
	else if (keycode == LEFT)
		data->keyboard.left = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == ESCAPE)
		data->keyboard.esc = 0;
	else if (keycode == W_KEY)
		data->keyboard.w = 0;
	else if (keycode == A_KEY)
		data->keyboard.a = 0;
	else if (keycode == S_KEY)
		data->keyboard.s = 0;
	else if (keycode == D_KEY)
		data->keyboard.d = 0;
	else if (keycode == RIGHT)
		data->keyboard.right = 0;
	else if (keycode == LEFT)
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
	else if (keycode == LEFT)
	{
		data->player_s.p_ang -= data->player_s.rot_speed;
		data->player_s.p_ang = FixAng(data->player_s.p_ang);
		data->player_s.delta_x = cos(degToRad(data->player_s.p_ang));
		data->player_s.delta_y = -sin(degToRad(data->player_s.p_ang));
	}
}

int	key_hook_manager(t_data *data)
{
	if (data->keyboard.esc)
		leave(data);
	else if (data->keyboard.w && hitbox_wall(data, data->player_s.p_ang))
		move_up(data);
	else if (data->keyboard.a && hitbox_wall(data, FixAng(data->player_s.p_ang - 90)))
		move_left(data);
	else if (data->keyboard.s && hitbox_wall(data, FixAng(data->player_s.p_ang + 180)))
			move_down(data);
	else if (data->keyboard.d && hitbox_wall(data, FixAng(data->player_s.p_ang + 90)))
		move_right(data);
	else if (data->keyboard.right)
		rotate_fov(RIGHT, data);
	else if (data->keyboard.left)
		rotate_fov(LEFT, data);
	draw_all(data);
	return (0);
}

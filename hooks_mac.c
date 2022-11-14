/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mac.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:55:14 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/14 18:21:16 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	leave(t_data *data)
{
	// mlx_destroy_image(data->mlx, data->ceiling.img_ptr);
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
	if (keycode == 1)
	{
	}
	// render(data);
	return (0);
}

void	move(int keycode, t_data *data)
{
	if (keycode == W_KEY)
	{
		if (hitbox_wall(data, data->player_s.p_ang))
			move_up(data);
	}
	else if (keycode == S_KEY)
	{
		if (hitbox_wall(data, FixAng(data->player_s.p_ang + 180)))
			move_down(data);
	}
	else if (keycode == A_KEY)
	{
		if (hitbox_wall(data, FixAng(data->player_s.p_ang - 90)))
			move_left(data);
	}
	else if (keycode == D_KEY)
	{
		if (hitbox_wall(data, FixAng(data->player_s.p_ang + 90)))
			move_right(data);
	}
	draw_all(data);
}

void	rotate_fov(int keycode, t_data *data)
{
	if (keycode == RIGHT)
	{
		data->player_s.p_ang += data->player_s.speed;
		data->player_s.p_ang = FixAng(data->player_s.p_ang);
		data->player_s.delta_x = cos(degToRad(data->player_s.p_ang));
		data->player_s.delta_y = -sin(degToRad(data->player_s.p_ang));
	}
	else if (keycode == LEFT)
	{
		data->player_s.p_ang -= data->player_s.speed;
		data->player_s.p_ang = FixAng(data->player_s.p_ang);
		data->player_s.delta_x = cos(degToRad(data->player_s.p_ang));
		data->player_s.delta_y = -sin(degToRad(data->player_s.p_ang));
	}
	draw_all(data);
}

int	key_hook_manager(int keycode, t_data *data)
{
	if (keycode == 53)
		leave(data);
	else if (keycode == W_KEY || keycode == S_KEY 
		|| keycode == D_KEY || keycode == A_KEY)
		move(keycode, data);
	else if (keycode == LEFT || keycode == RIGHT)
		rotate_fov(keycode, data);
	else
		printf("Key %d was pressed!\n", keycode);
	return (0);
}

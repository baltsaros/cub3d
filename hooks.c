/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:55:14 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/13 17:48:27 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	is_wall(char **map, int x, int y, int flag)
// {
// 	int	rx;
// 	int	ry;

// 	ry = y / SQUARE_SIZE;
// 	rx = x / SQUARE_SIZE;
// 	if (map[ry][rx] && map[ry][rx] != '1')
// 		return (1);
// 	return (0);
// }

int		render(t_data *data)
{
	(void)data;
	return (0);
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
	if (keycode == 119)
	{
		data->player_s.pos_win_y += (data->player_s.speed * data->player_s.delta_y) / 2;
		data->player_s.pos_win_x += (data->player_s.speed * data->player_s.delta_x) / 2;
		data->player_s.pos_y += data->player_s.speed * data->player_s.delta_y;
		data->player_s.pos_x += data->player_s.speed * data->player_s.delta_x;
	}
	else if (keycode == 115)
	{
		data->player_s.pos_win_y -= (data->player_s.speed * data->player_s.delta_y) / 2;
		data->player_s.pos_win_x -= (data->player_s.speed * data->player_s.delta_x) / 2;
		data->player_s.pos_y -= data->player_s.speed * data->player_s.delta_y;
		data->player_s.pos_x -= data->player_s.speed * data->player_s.delta_x;
	}
	else if (keycode == 97)
	{
		data->player_s.pos_win_y += (data->player_s.speed * sin(data->player_s.p_ang - ((90 * M_PI) / 180))) / 2;
		data->player_s.pos_win_x += (data->player_s.speed * cos(data->player_s.p_ang - ((90 * M_PI) / 180))) / 2;
		data->player_s.pos_y += data->player_s.speed * sin(data->player_s.p_ang - ((90 * M_PI) / 180));
		data->player_s.pos_x += data->player_s.speed * cos(data->player_s.p_ang - ((90 * M_PI) / 180));
	}
	else if (keycode == 100)
	{
		data->player_s.pos_win_y -= (data->player_s.speed * sin(data->player_s.p_ang - ((90 * M_PI) / 180))) / 2;
		data->player_s.pos_win_x -= (data->player_s.speed * cos(data->player_s.p_ang - ((90 * M_PI) / 180))) / 2;
		data->player_s.pos_y -= data->player_s.speed * sin(data->player_s.p_ang - ((90 * M_PI) / 180));
		data->player_s.pos_x -= data->player_s.speed * cos(data->player_s.p_ang - ((90 * M_PI) / 180));
	}
}

void	rotate_fov(int keycode, t_data *data)
{
	if (keycode == 65361)
	{
		data->player_s.p_ang += data->player_s.speed;
		data->player_s.p_ang = FixAng(data->player_s.p_ang);
		data->player_s.delta_x = cos(degToRad(data->player_s.p_ang));
		data->player_s.delta_y = -sin(degToRad(data->player_s.p_ang));
	}
	else if (keycode == 65363)
	{
		data->player_s.p_ang -= data->player_s.speed;
		data->player_s.p_ang = FixAng(data->player_s.p_ang);
		data->player_s.delta_x = cos(degToRad(data->player_s.p_ang));
		data->player_s.delta_y = -sin(degToRad(data->player_s.p_ang));
	}
}

int	key_hook_manager(int keycode, t_data *data)
{
	if (keycode == 65307)
		leave(data);
	else if (keycode == 119 || keycode == 115 || keycode == 100 || keycode == 97)
		move(keycode, data);
	else if (keycode == 65363 || keycode == 65361)
		rotate_fov(keycode, data);
	else
		printf("Key %d was pressed!\n", keycode);
	return (0);
}

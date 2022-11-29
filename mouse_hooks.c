/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:22:08 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/29 16:28:00 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifdef __linux__

int	mouse_hook(int x, int y, t_data *data)
{
	if (data->keyboard.shift)
	{
		mlx_mouse_show(data->mlx, data->win);
		return (0);
	}
	mlx_mouse_hide(data->mlx, data->win);
	mlx_mouse_move(data->mlx, data->win, WIDTH / 2, HEIGHT / 2);
	if (y != HEIGHT / 2)
		y = HEIGHT / 2;
	if (x > WIDTH / 2)
		data->player_s.p_ang -= data->player_s.rot_speed;
	else if (x < WIDTH / 2)
		data->player_s.p_ang += data->player_s.rot_speed;
	else
		return (0);
	data->player_s.p_ang = fixang(data->player_s.p_ang);
	data->player_s.delta_x = cos(degtorad(data->player_s.p_ang));
	data->player_s.delta_y = -sin(degtorad(data->player_s.p_ang));
	return (0);
}
#else

int	mouse_hook(int x, int y, t_data *data)
{
	int	rot_diff;

	(void)y;
	if (data->keyboard.shift)
		return (0);
	if (x > WIDTH / 2)
		rot_diff = x - (WIDTH / 2);
	else if (x < WIDTH / 2)
		rot_diff = (WIDTH / 2) - x;
	else
		return (0);
	if (x > WIDTH / 2)
		data->player_s.p_ang -= rot_diff / 10;
	else if (x < WIDTH / 2)
		data->player_s.p_ang += rot_diff / 10;
	data->player_s.p_ang = fixang(data->player_s.p_ang);
	data->player_s.delta_x = cos(degtorad(data->player_s.p_ang));
	data->player_s.delta_y = -sin(degtorad(data->player_s.p_ang));
	return (0);
}
#endif
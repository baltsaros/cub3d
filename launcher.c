/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:11:23 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/07 17:00:58 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hook_manager(t_data *data)
{
	mlx_hook(data->win, 2, (1L << 0), key_hook_manager, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_hook(data->win, 17, 1L << 17, ft_exit, data);
	mlx_loop_hook(data->mlx, infinite_hook, &data);
}

int		launcher(t_data *data)
{
	data->mlx = mlx_init();
	check_mlx(data->mlx, data);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	check_win(data);
	init_minimap_values(data);
	init_player_values(data);
	printf("angle: %f, x: %f, y: %f, x_w: %f, y_w: %f\n", data->player_s.p_ang,
		data->player_s.pos_x, data->player_s.pos_y, data->player_s.pos_win_x, data->player_s.pos_win_y);
	printf("x_m: %d, y_m: %d\n", data->minimap_s.position.x, data->minimap_s.position.y);  
	draw_all(data);
	hook_manager(data);
	mlx_loop(data->mlx);
	return (0);
}
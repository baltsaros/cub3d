/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:11:23 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/19 15:43:14 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_mlx_and_window(t_data *data)
{
    data->mlx = mlx_init();
    check_mlx(data->mlx, data);
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    check_win(data);
    data->pos_x_minimap = 10;
    data->pos_y_minimap = 10;
    data->size_player = 11;
    data->size_square = 55;
    data->player_s.p_ang = 60;
    data->player_s.delta_x = cos(degToRad(data->player_s.p_ang));
	data->player_s.delta_y = -sin(degToRad(data->player_s.p_ang));
}

int launcher(t_data *data)
{
    init_mlx_and_window(data);
    draw_all(data);
    
    mlx_hook(data->win, 2, (1L << 0), key_hook_manager, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_hook(data->win, 17, 1L << 17, ft_exit, data);
    mlx_loop_hook(data->mlx, infinite_hook, &data);
    mlx_loop(data->mlx);
    return (0);
}
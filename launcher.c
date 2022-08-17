/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:11:23 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/17 18:40:45 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_mlx_and_window(t_data *data)
{
    data->mlx = mlx_init();
    check_mlx(data->mlx, data);
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    check_win(data);
    data->pos_x_minimap = (WIDTH / 2) - ((data->map.width * 50) / 2);
    data->pos_y_minimap = (HEIGHT / 2) - ((data->map.height * 50) / 2);
    data->size_player = 10;
    data->size_square = 50;
}

int launcher(t_data *data)
{
    init_mlx_and_window(data);
    draw_all(data);

    mlx_key_hook(data->win, key_hook, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_hook(data->win, 17, 1L << 17, ft_exit, data);
    mlx_loop_hook(data->mlx, infinite_hook, &data);
    mlx_loop(data->mlx);
    return (0);
}
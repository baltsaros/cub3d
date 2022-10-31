/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:11:23 by mthiry            #+#    #+#             */
/*   Updated: 2022/10/31 15:08:35 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    hook_manager(t_data *data)
{
    mlx_hook(data->win, 2, (1L << 0), key_hook_manager, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_hook(data->win, 17, 1L << 17, ft_exit, data);
    mlx_loop_hook(data->mlx, infinite_hook, &data);
}

int launcher(t_data *data)
{
    data->mlx = mlx_init();
    check_mlx(data->mlx, data);
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    check_win(data);
    init_minimap_values(data);
    init_player_values(data);
    printf("drawing\n");
    draw_all(data);

    hook_manager(data);
    mlx_loop(data->mlx);
    return (0);
}
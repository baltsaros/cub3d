/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:11:23 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/16 15:11:56 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_mlx_and_window(t_data *data)
{
    data->mlx = mlx_init();
    check_mlx(data->mlx, data);
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    check_win(data);
}

int launcher(t_data *data)
{
    init_mlx_and_window(data);
    for(int i = 0; data->map.raw[i]; i++)
        printf("%s\n", data->map.raw[i]);
    mlx_key_hook(data->win, key_hook, &data);
	mlx_mouse_hook(data->win, mouse_hook, &data);
	mlx_hook(data->win, 17, 1L << 17, ft_exit, &data);
    mlx_loop(data->mlx);
    return (0);
}
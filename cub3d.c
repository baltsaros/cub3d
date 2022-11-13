/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:03:00 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/13 19:08:41 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hook_manager(t_data *data)
{
	mlx_hook(data->win, 2, (1L << 0), key_hook_manager, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_hook(data->win, 17, 1L << 17, ft_exit, data);
	mlx_loop_hook(data->mlx, draw_all, &data);
}

int		launcher(t_data *data)
{
	int ret;

	ret = 0;
	data->mlx = mlx_init();
	check_mlx(data->mlx, data);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	check_win(data);
	ret = init_minimap_values(data);
	if (ret != 0)
		return (ret);
	ret = init_player_values(data);
	if (ret != 0)
		return (ret);
	ret = load_textures(data);
	if (ret != 0)
		return (ret);
	ret = init_img(data);
	if (ret != 0)
		return (ret);
	draw_all(data);
	hook_manager(data);
	mlx_loop(data->mlx);
	return (ret);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		error_exit(&data, "Ivalid amount of arguments", 0);
	init_map(&data, argv[1]);
	return (launcher(&data));
}

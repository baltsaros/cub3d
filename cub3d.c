/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:03:00 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/25 15:24:51 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hook_manager(t_data *data)
{
	data->keyboard.esc = 0;
	data->keyboard.w = 0;
	data->keyboard.a = 0;
	data->keyboard.s = 0;
	data->keyboard.d = 0;
	data->keyboard.right = 0;
	data->keyboard.left = 0;
	data->keyboard.shift = 0;
	mlx_hook(data->win, KEYPRESS, KEYPRESSMASK, key_press, data);
	mlx_hook(data->win, KEYRELEASE, KEYRELEASEMASK, key_release, data);
	mlx_hook(data->win, MOUSEMOVE, BUTTONMOTION, mouse_hook, data);
	mlx_hook(data->win, DESTROY, STRUCTURENOT, ft_exit, data);
	mlx_loop_hook(data->mlx, key_hook_manager, data);
	mlx_loop(data->mlx);
}

int	launcher(t_data *data)
{
	data->mlx = mlx_init();
	check_mlx(data->mlx, data);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	check_win(data);
	init_minimap(data);
	init_player_values(data);
	if (load_textures(data))
		leave(data, EXIT_FAILURE);
	if (init_img(data))
		leave(data, EXIT_FAILURE);
	init_background(data);
	hook_manager(data);
	return (EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	int		ret;
	t_data	data;

	if (argc != 2)
		error_exit(&data, "Invalid amount of arguments", 0);
	init_img_null(&data);
	init_map(&data, argv[1]);
	ret = launcher(&data);
	leave(&data, ret);
	return (1);
}

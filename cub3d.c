/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:03:00 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/22 14:15:06 by abuzdin          ###   ########.fr       */
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
	mlx_hook(data->win, KEYPRESS, KEYPRESSMASK, key_press, data);
	mlx_hook(data->win, KEYRELEASE, KEYRELEASEMASK, key_release, data);
	mlx_hook(data->win, MOUSEMOVE, BUTTONMOTION, mouse_hook, data);
	mlx_hook(data->win, DESTROY, STRUCTURENOT, ft_exit, data);
	mlx_loop_hook(data->mlx, key_hook_manager, data);
	mlx_loop(data->mlx);
}

void	init_static_img_addr(t_data *data)
{	
	init_background(data);
	ft_memset(data->player.addr, data->player.basic_color,
		PLAYER_SIZE * sizeof(int));
}

int	launcher(t_data *data)
{
	data->mlx = mlx_init();
	check_mlx(data->mlx, data);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	check_win(data);
	init_minimap_values(data);
	init_player_values(data);
	init_img_null(data);
	if (load_textures(data))
		leave(data, EXIT_FAILURE);
	if (init_img(data))
		leave(data, EXIT_FAILURE);
	init_static_img_addr(data);
	hook_manager(data);
	return (EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	int		ret;
	t_data	data;

	if (argc != 2)
		error_exit(&data, "Invalid amount of arguments", 0);
	init_map(&data, argv[1]);
	ret = launcher(&data);
	leave(&data, ret);
	return (1);
}

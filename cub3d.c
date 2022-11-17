/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:03:00 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/17 09:28:39 by abuzdin          ###   ########.fr       */
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
	mlx_hook(data->win, 6, 1L<<12, mouse_hook, data);
	// mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_loop_hook(data->mlx, key_hook_manager, data);
	// mlx_loop_hook(data->mlx, draw_all, &data);
	mlx_hook(data->win, 17, 1L<<17, ft_exit, data);
}

int		launcher(t_data *data)
{
	int ret;

	data->x = WIDTH / 2;
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

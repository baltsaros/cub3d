/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:03:00 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/28 17:35:30 by mthiry           ###   ########.fr       */
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
	data->anim = 0;
	mlx_hook(data->win, KEYPRESS, KEYPRESSMASK, key_press, data);
	mlx_hook(data->win, KEYRELEASE, KEYRELEASEMASK, key_release, data);
	mlx_hook(data->win, MOUSEMOVE, BUTTONMOTION, mouse_hook, data);
	mlx_hook(data->win, DESTROY, STRUCTURENOT, ft_exit, data);
	mlx_loop_hook(data->mlx, key_hook_manager, data);
	mlx_loop(data->mlx);
}

int	launcher(t_data *data)
{
	int	ret;

	data->mlx = mlx_init();
	check_mlx(data->mlx, data);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	check_win(data);
	init_minimap(data);
	init_player_values(data);
	ret = init_depth(data);
	if (ret != 0)
		check_errors(data, ret);
	ret = init_sprites(data);
	if (ret != 0)
		check_errors(data, ret);
	ret = load_textures(data);
	if (ret != 0)
		check_errors(data, ret);
	ret = load_sprites_textures(data);
	if (ret != 0)
		check_errors(data, ret);
	ret = init_img(data);
	if (ret != 0)
		check_errors(data, ret);
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
	data.is_depth_allocated = 0;
	data.is_objs_allocated = 0;
	init_map(&data, argv[1]);
	ret = launcher(&data);
	leave(&data, ret);
	return (1);
}

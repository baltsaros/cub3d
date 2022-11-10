/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:11:23 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/10 11:26:42 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hook_manager(t_data *data)
{
	mlx_hook(data->win, 2, (1L << 0), key_hook_manager, data);
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_hook(data->win, 17, 1L << 17, ft_exit, data);
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
	// Ceiling
	data->ceiling.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT / 2);
	// printf("ceiling\n");
	if (data->ceiling.img_ptr != NULL)
		init_ceiling(data);
	// Floors
	data->floor.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT / 2);
	// printf("floor\n");
	if (data->floor.img_ptr != NULL)
		init_floor(data);
	//else
		// put error here
	data->minimap.basic_color = 0x000000;
	data->minimap.addr = mlx_get_data_addr(data->minimap.img_ptr, &data->minimap.bpp,
		&data->minimap.line_length, &data->minimap.endian);
	data->player.basic_color = 0x0FAE2;
	data->player.addr = mlx_get_data_addr(data->player.img_ptr, &data->player.bpp,
			&data->player.line_length, &data->player.endian);
	data->ray.img_ptr = mlx_new_image(data->mlx, data->minimap_s.width, data->minimap_s.height);
	// if (!data->ray_s.ray.img_ptr)
	// // Put error here
	data->ray.basic_color = 0xFFFFFF;
	data->ray.addr = mlx_get_data_addr(data->ray.img_ptr, &data->ray.bpp,
		  &data->ray.line_length, &data->ray.endian);
	data->walls.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->walls.basic_color = 0x00BFFF;
	data->walls.addr = mlx_get_data_addr(data->walls.img_ptr, &data->walls.bpp,
		&data->walls.line_length, &data->walls.endian);
	hook_manager(data);
	// draw_all(data);
	mlx_loop_hook(data->mlx, draw_all, data);
	mlx_loop(data->mlx);
	return (0);
}
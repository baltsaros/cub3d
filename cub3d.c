#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_input	data;

	if (argc != 2)
		error_exit(&data, "Ivalid amount of arguments", 0);
	init_map(&data, argv[1]);
	data.mlx = mlx_init();
	check_mlx(data.mlx, &data);
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "cub3d");
	check_win(&data);
	data.img.mlx_img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_length, &data.img.endian);
	data.pl.mlx_img = mlx_new_image(data.mlx, data.sx, data.sy);
	data.pl.addr = mlx_get_data_addr(data.pl.mlx_img, &data.pl.bpp,
			&data.pl.line_length, &data.pl.endian);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_hook(data.win, 17, 1L << 17, ft_exit, &data);
	mlx_loop(data.mlx);
	return (0);
}

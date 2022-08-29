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
	data.pcoord[0] = data.px;
	data.pcoord[1] = data.py;
	data.px = data.px * data.sx;
	data.py = data.py * data.sy;
	// if (data.map.dir == 'N')
	// 	data.pa = (90 * PI) / 180;
	// else if (data.map.dir == 'E')
	// 	data.pa = (0 * PI) / 180;
	// else if (data.map.dir == 'W')
	// 	data.pa = (180 * PI) / 180;
	// else if (data.map.dir == 'S')
	// 	data.pa = (270 * PI) / 180;
	// data.ra = (60 * PI) / 180;
	// data.rdx = cos(data.ra);
	// data.rdy = sin(data.ra);
	// data.la = (120 * PI) / 180;
	// data.ldx = cos(data.la);
	// data.ldy = sin(data.la);
	// data.pdx = cos(data.pa);
	// data.pdy = sin(data.pa);
	data.psize = 8;
	data.pl.mlx_img = mlx_new_image(data.mlx, data.psize, data.psize);
	data.pl.addr = mlx_get_data_addr(data.pl.mlx_img, &data.pl.bpp,
			&data.pl.line_length, &data.pl.endian);
	// printf("dir is %c\n", data.map.dir);
	// printf("pa is %f\npdx is %f\npdy is %f\n", data.pa, data.pdx, data.pdy);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_hook(data.win, 17, 1L << 17, ft_exit, &data);
	mlx_loop(data.mlx);
	return (0);
}

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		error_exit(&data, "Ivalid amount of arguments", 0);
	init_map(&data, argv[1]);
	return (launcher(&data));

	// data.img.mlx_img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	// data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
	// 		&data.img.line_length, &data.img.endian);
}

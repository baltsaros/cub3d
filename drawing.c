#include "cub3d.h"

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}


void	render(t_input *data)
{
	render_background(data, &data->img);
	render_player(data, &data->img);
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
}

void	render_background(t_input *data, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	data->color = encode_rgb(100, 0, 50);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(img, x, y, data->color);
			++x;
		}
		++y;
	}
}

void	render_player(t_input *data, t_img *img)
{
	// float	x;
	// float	y;

	// y = 200;
	// data->color = encode_rgb(100, 0, 50);
	// while (y < data->py)
	// {
	// 	x = 200;
	// 	while (x < data->px)
	// 	{
	// 		my_mlx_pixel_put(img, x, y, 0xFF00);
	// 		++x;
	// 	}
	// 	++y;
	// }
	my_mlx_pixel_put(img, data->px, data->py, 0xFF00);
}
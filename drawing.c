#include "cub3d.h"

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}


void	render(t_input *data)
{
	// render_background(data, &data->img);
	// data->color = encode_rgb(100, 0, 50);
	render_map(data, data->map.map);
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
}

void	render_map(t_input *data, char **map)
{
	int	i;
	int	j;

	j = 0;
	while(map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == '1')
				render_elem(data, GRAY, j, i);
			else if (map[j][i] == '0')
				render_elem(data, WHITE, j, i);
			else if (check_charset(map[j][i], "NEWS"))
				render_elem(data, RED, j, i);
			else
				render_elem(data, BLACK, j, i);
			++i;
		}
		++j;
	}
}

void	render_elem(t_input *data, int color, int j, int i)
{
	float	x;
	float	y;

	y = data->sy * j;
	while (y < HEIGHT && y < y + data->sy)
	{
		x = data->sx * i;
		while (x < WIDTH && x < x + data->sx)
		{
			my_mlx_pixel_put(&data->img, x, y, color);
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
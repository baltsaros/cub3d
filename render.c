#include "cub3d.h"

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

void	render_blok(t_input *data, t_img *img)
{
	float	x;
	float	y;

	(void)data;
	y = 100;
	while (y < 110)
	{
		x = 100;
		while (x < 110)
		{
			printf("%f\n", x);
			my_mlx_pixel_put(img, x, y, GREEN);
			++x;
		}
		++y;
	}
}

int	render(t_input *data)
{
	// render_background(data, &data->img);
	render_map(data, data->map.map);
	render_player(data, &data->img);
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	render_blok(data, &data->blok);
	printf("blok\n");
	mlx_put_image_to_window(data->mlx, data->win, data->blok.mlx_img, 10, 10);
	return (0);
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
			else if (map[j][i] == '0' || check_charset(map[j][i], "NEWS"))
				render_elem(data, WHITE, j, i);
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
	while (y < data->sy * (j + 1) - 1)
	{
		x = data->sx * i;
		while (x < data->sx * (i + 1) - 1)
		{
			my_mlx_pixel_put(&data->img, x, y, color);
			++x;
		}
		++y;
	}
}

void	render_player(t_input *data, t_img *img)
{
	float	x;
	float	y;

	y = data->py * data->sy;
	data->color = encode_rgb(100, 0, 50);
	while (y < data->sy * (data->py + 1))
	{
		x = data->px * data->sx;
		while (x < data->sx * (data->px + 1))
		{
			my_mlx_pixel_put(img, x, y, data->color);
			++x;
		}
		++y;
	}
}

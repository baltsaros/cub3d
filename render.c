#include "cub3d.h"

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}


int	render(t_input *data)
{
	render_map(data, data->map.map);
	render_ray(data, RED);
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	render_player(data, &data->pl);
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

	y = 0;
	data->color = encode_rgb(100, 0, 50);
	while (y < data->psize)
	{
		x = 0;
		while (x < data->psize)
		{
			my_mlx_pixel_put(img, x, y, data->color);
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(data->mlx, data->win, img->mlx_img, data->px, data->py);
}

int	iss_wall(t_input *data, char **map, float x, float y)
{
	int	rx;
	int	ry;

	ry = y / data->sy;
	rx = x / data->sx;
	// printf("rx is %d, ry is %d\n", rx, ry);
	// printf("map[%d][%d] is %c\n", ry, rx, map[ry][rx]);
	// printf("px is %f, py is %f\n", data->px, data->py);
	if (map[ry][rx] && map[ry][rx] != '1')
		return (1);
	return (0);
}

void	render_ray(t_input *data, int color)
{
	float	x;
	float	y;
	int		j;

	j = 0;
	y = data->py + data->psize / 2;
	x = data->px + data->psize / 2;
	data->ry = y;
	data->rx = x;
	data->ly = y;
	data->lx = x;
	while (j < 40)
	{
		my_mlx_pixel_put(&data->img, x, y, color);
		if (iss_wall(data, data->map.map, data->rx, data->ry))
			my_mlx_pixel_put(&data->img, data->rx, data->ry, RED);
		if (iss_wall(data, data->map.map, data->lx, data->ly))
			my_mlx_pixel_put(&data->img, data->lx, data->ly, RED);
		data->lx += data->ldx;
		data->ly += data->ldy;
		data->rx += data->rdx;
		data->ry += data->rdy;
		x += data->pdx;
		y += data->pdy;
		++j;
	}

}
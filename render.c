#include "cub3d.h"

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}


int	render(t_input *data)
{
	render_background(data);
	render_map(data, data->map.map);
	render_rays(data, RED);
	// render_mray(data, RED);
	// render_lray(data, RED);
	// render_rray(data, RED);
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	render_player(data, &data->pl);
	return (0);
}

void	render_background(t_input *data)
{
	int	x;
	int	y;

	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&data->img, x, y, BLACK);
			++x;
		}
		++y;
	}
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

void	render_rays(t_input *data, int color)
{
	float	angle;

	angle = 0;
	while (angle < 60)
	{
		data->ly = data->py + data->psize / 2;
		data->lx = data->px + data->psize / 2;
		data->ldx = cos(data->la + (angle * PI / 180));
		data->ldy = sin(data->la + (angle * PI / 180));
		while (is_wall(data, data->map.map, data->lx, data->ly))
		{
			my_mlx_pixel_put(&data->img, data->lx, data->ly, color);
			data->lx += data->ldx;
			data->ly += data->ldy;
		}
		angle += 0.5;
		// angle++;
	}
}

void	rendle_mray(t_input *data, int color)
{
	float	x;
	float	y;
	int		j;

	j = 0;
	y = data->py + data->psize / 2;
	x = data->px + data->psize / 2;
	while (j < 40)
	{
		my_mlx_pixel_put(&data->img, x, y, color);
		x += data->pdx;
		y += data->pdy;
		++j;
	}
}

void	render_lray(t_input *data, int color)
{
	data->ly = data->py + data->psize / 2;
	data->lx = data->px + data->psize / 2;
	while (is_wall(data, data->map.map, data->lx, data->ly))
	{
		my_mlx_pixel_put(&data->img, data->lx, data->ly, color);
		data->lx += data->ldx;
		data->ly += data->ldy;
	}
}

void	render_rray(t_input *data, int color)
{
	data->ry = data->py + data->psize / 2;
	data->rx = data->px + data->psize / 2;
	while (is_wall(data, data->map.map, data->rx, data->ry))
	{
		my_mlx_pixel_put(&data->img, data->rx, data->ry, color);
		data->rx += data->rdx;
		data->ry += data->rdy;
	}
}

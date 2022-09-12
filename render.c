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
	render_mray(data, GREEN);
	// new_ray(data, RED);
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

// void	new_ray(t_input *data, int color)
// {
// 	float	rx;
// 	float	ry;
// 	int		x;
// 	int		y;
// 	float	cam;
// 	float	sdx;
// 	float	sdy;
// 	float	ddx;
// 	float	ddy;
// 	float	walld;
// 	int		mapx;
// 	int		mapy;
// 	int		stepx;
// 	int		stepy;
// 	int		side;
// 	int		hit = 0;

// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		cam = 2 * x / WIDTH - data->sx;
// 		rx = data->xx + data->pdx * cam;
// 		ry = data->yy + data->pdy * cam;
// 		x++;
// 		mapx = data->px;
// 		mapy = data->py;
// 		ddx = (rx == 0) ? 1e30 : fabs(1 / rx);
// 		ddy = (ry == 0) ? 1e30 : fabs(1 / ry);
// 		if (rx < 0)
// 		{
// 			stepx = -data->sx;
// 			sdx = (data->px - mapx) * ddx;
// 		}
// 		else
// 		{
// 			stepx = data->sx;
// 			sdx = (mapx + data->sx - data->px) * ddx;
// 		}
// 		if (ry < 0)
// 		{
// 			stepy = -data->sy;
// 			sdy = (data->py - mapy) * ddy;
// 		}
// 		else
// 		{
// 			stepy = data->sy;
// 			sdy = (mapy + data->sy - data->py) * ddy;
// 		}
// 		while (hit == 0)
// 		{
// 			if (sdx < sdy)
// 			{
// 				sdx += ddx;
// 				mapx += stepx;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sdy += ddy;
// 				mapy += stepy;
// 				side = 1;
// 			}
// 			if (!is_wall(data, data->map.map, mapx, mapy))
// 				hit = 1;
// 		}
// 		if (side == 0)
// 			walld = sdx - ddx;
// 		else
// 			walld = sdy - ddy;
		
// 		int	lheight = (int)(HEIGHT/walld);
// 		int	drawstart = -lheight / 2 + HEIGHT / 2;
// 		if (drawstart < 0)
// 			drawstart = 0;
// 		int	drawend	= lheight / 2 + HEIGHT / 2;
// 		if (drawend >= HEIGHT)
// 			drawend = HEIGHT - data->sy;
// 		y = drawstart;
// 		while (y < drawend)
// 		{
// 			my_mlx_pixel_put(&data->img, x, y, color);
// 			++y;
// 		}
// 	}
// }

void	render_rays(t_input *data, int color)
{
	float	angle;
	float	dist;
	int		nceil;
	int		nfloor;
	int		y;
	int		x;
	int		w;
	float	z;

	(void)color;
	angle = 0.0f;
	x = 0;
	w = data->sx/2;
	while (angle < 60)
	{
		dist = 0.0f;
		data->ly = data->py + data->psize / 2;
		data->lx = data->px + data->psize / 2;
		data->ldx = cos(data->la + (angle * PI / 180));
		data->ldy = -sin(data->la + (angle * PI / 180));
		// data->ldx = cos(data->la + (angle * PI / 180)) * data->sx;
		// data->ldy = -sin(data->la + (angle * PI / 180)) * data->sy;
		while (is_wall(data, data->map.map, data->lx, data->ly) && z < 16.0)
		{
			my_mlx_pixel_put(&data->img, data->lx, data->ly, color);
			data->lx += data->ldx;
			data->ly += data->ldy;
			dist += 0.1;
			z = dist * data->pdx;
			// printf("lx is %f, ly is %f\n", data->lx, data->ly);
		}
		angle += 0.5;
		nceil = HEIGHT / 2.0f - HEIGHT/dist;
		nfloor = HEIGHT - nceil;
		while (x < w && w < WIDTH)
		{
			y = nceil;
			while (y < nfloor - z)
			{
				if (dist > 15.9f)
					my_mlx_pixel_put(&data->img, x, y, GRAY);
				else
					my_mlx_pixel_put(&data->img, x, y, 420 + (3 * dist));
				++y;
			}
			++x;
		}
		w += data->sx/2;
		angle++;
		printf("ceiling is %d, floor is %d\n", nceil, nfloor);
	}
}

// old functions
void	render_mray(t_input *data, int color)
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
		data->xx = x;
		data->yy = y;
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

#include "cub3d.h"

void	check_direction(t_input *data)
{
	if (data->map.dir == 'N')
		data->map.angle = 90;
	else if (data->map.dir == 'E')
		data->map.angle = 360;
	else if (data->map.dir == 'W')
		data->map.angle = 180;
	else if (data->map.dir == 'S')
		data->map.angle = 270;
	data->pa = ((data->map.angle % 360) * PI) / 180;
	data->rdx = cos(data->ra);
	data->rdy = -sin(data->ra);
	data->la = data->pa - (30 * PI) / 180;
	data->ra = data->pa + (30 * PI) / 180;
	// printf("pa is %f, la is %f\n", data->pa, data->la);
	// printf("pa is %f, la is %f\n", (data->pa * 180) / PI, (data->la * 180) / PI);
	data->ldx = cos(data->la);
	data->ldy = -sin(data->la);
	data->pdx = cos(data->pa);
	data->pdy = -sin(data->pa);
}

void	squarification(t_input *data, char **map)
{
	char	**tmp;

	(void)map;
	if (data->map.width == data->map.height)
		return ;
	if (data->map.width < data->map.height)
		data->map.width = data->map.height;
	else
		data->map.height = data->map.width;
	tmp = cub_malloc(sizeof(char*) * (data->map.height + 1), data);
	data->i = 0;
	while (data->i < data->map.height)
	{
		tmp[data->i] = ft_calloc(data->map.width + 1, 1);
		alloc_check_small(tmp[data->i], data);
		tmp[data->i] = ft_memset(tmp[data->i], ' ', data->map.width);
		data->i++;
	}
	tmp[data->i] = NULL;
	data->i = 0;
	while (map[data->i])
	{
		tmp[data->i] = ft_memcpy(tmp[data->i], map[data->i], data->map.width);
		data->i++;
	}
}

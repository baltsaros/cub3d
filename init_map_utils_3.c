#include "cub3d.h"

void	check_direction(t_data *data)
{
	if (data->map.dir == 'N')
		data->map.angle = 90;
	else if (data->map.dir == 'E')
		data->map.angle = 360;
	else if (data->map.dir == 'W')
		data->map.angle = 180;
	else if (data->map.dir == 'S')
		data->map.angle = 270;
	data->player_s.p_ang = data->map.angle;
	// data->player_s.p_ang = ((data->map.angle % 360) * PI) / 180;
}

void	squarification(t_data *data, char **map)
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

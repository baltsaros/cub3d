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
	data->ra = ((data->map.angle % 360 + 30) * PI) / 180;
	data->rdx = cos(data->ra);
	data->rdy = sin(data->ra);
	data->la = ((data->map.angle % 360 - 30) * PI) / 180;
	data->ldx = cos(data->la);
	data->ldy = sin(data->la);
	data->pdx = cos(data->pa);
	data->pdy = sin(data->pa);
}

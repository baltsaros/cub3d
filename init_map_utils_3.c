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

void	print_map(t_data *data, char **map)
{
	size_t	i;

	i = 0;
	printf("\nDirection: %c\n", data->map.dir);
	printf("Players coord: (%d, %d)\n", data->map.coord[1], data->map.coord[0]);
	printf("Map size: %ld x %ld\n", data->map.width, data->map.height);
	printf("MAP:\n\n");
	while (map[i])
	{
		printf("%s\n", map[i]);
		++i;
	}
}

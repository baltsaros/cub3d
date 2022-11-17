#include "cub3d.h"

void	cub_free(char *str[])
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		++i;
	}
	free(str);
}

void	cub_free_params(t_data *data)
{
	cub_free(data->map.raw);
	if (data->map.no)
		free(data->map.no);
	if (data->map.so)
		free(data->map.so);
	if (data->map.we)
		free(data->map.we);
	if (data->map.ea)
		free(data->map.ea);
	if (data->map.f)
		free(data->map.f);
	if (data->map.c)
		free(data->map.c);
	cub_free(data->map.f_spl);
	cub_free(data->map.c_spl);
	cub_free(data->map.map);
}

void	cub_free_all(t_data *data)
{
	cub_free_params(data);
}

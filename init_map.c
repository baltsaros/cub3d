/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:13:40 by mthiry            #+#    #+#             */
/*   Updated: 2022/08/15 14:56:33 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	**init_empty_map(char **args_map, int row, int col)
// {
// 	int	i;
// 	int	**map;

// 	i = 0;
// 	map = (int **) malloc (row * sizeof(int *));
// 	if (!map)
// 		free_strarray_error_and_exit(args_map, strerror(errno));
// 	while (i < row)
// 	{
// 		map[i] = (int *) malloc (col * sizeof(int));
// 		if (!map)
// 		{
// 			free_all_int_array(map, row);
// 			free_strarray_error_and_exit(args_map, strerror(errno));
// 		}
// 		i++;
// 	}
// 	return (map);
// }

// int	*init_line(char **tmp, int *line, int col)
// {
// 	int	i;

// 	i = 0;
// 	while (tmp[i] && i < col)
// 	{
// 		line[i] = ft_atoi(tmp[i]);
// 		i++;
// 	}
// 	return (line);
// }

// int	**fill_map(char **args_map, int **map, int row, int col)
// {
// 	int		i;
// 	char	**tmp;

// 	i = 0;
// 	while (args_map[i] && i < row)
// 	{
// 		tmp = ft_split(args_map[i], ' ');
// 		if (!tmp)
// 		{
// 			free_all_int_array(map, row);
// 			free_strarray_error_and_exit(args_map, strerror(errno));
// 		}
// 		map[i] = init_line(tmp, map[i], col);
// 		free_all_array(tmp);
// 		i++;
// 	}
// 	return (map);
// }

t_map	read_map(t_input *data, char *arg)
{
	t_map	map;
	char	*buf;
	char	*line;

	buf = cub_strdup("", data);
	data->fd = open(arg, O_RDONLY);
	error_check_exit(data->fd, "open", data);
	while (19)
	{
		line = get_next_line(data->fd, data);
		if (!line)
			break ;
		buf = cub_strjoin_free(buf, line, data);
		free(line);
	}
	map.raw = ft_split(buf, '\n');
	alloc_check_big(map.raw, data);
	printf("%s\n", buf);
	free(buf);
	return (map);
}

int	init_map(t_input *data, char *arg)
{
	data->map = read_map(data, arg);
	// args_map = get_args_map(args);
	// map.row = get_row(args_map);
	// map.col = get_col(args_map);
	// map.map = init_empty_map(args_map, map.row, map.col);
	// map.map = fill_map(args_map, map.map, map.row, map.col);
	// free_all_array(args_map);
	return (0);
}

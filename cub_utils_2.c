/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:09:01 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/25 21:01:34 by abuzdin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		++i;
	return (s1[i] - s2[i]);
}

char	*get_next_line(int fd, t_data *data)
{
	char	buf[1];
	char	*line;
	ssize_t	r_bytes;

	line = ft_calloc(1, sizeof(char));
	alloc_check_small(line, data);
	r_bytes = 1;
	while (r_bytes > 0)
	{
		r_bytes = read(fd, buf, 1);
		if (r_bytes < 0)
		{
			free(line);
			close(data->fd);
			error_check_exit(r_bytes, "read: ", data);
		}
		if (!r_bytes)
		{
			data->i = 0;
			break ;
		}
		line = cub_charjoin_free(line, buf[0], data);
		alloc_check_small(line, data);
	}
	return (line);
}

int	check_charset(char c, char *charset)
{
	unsigned int	i;

	i = 0;
	if (!charset)
		return (0);
	while (charset[i])
	{
		if (charset[i] == c)
			return (charset[i]);
		++i;
	}
	return (0);
}

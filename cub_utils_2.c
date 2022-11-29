/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:09:01 by abuzdin           #+#    #+#             */
/*   Updated: 2022/11/29 15:41:18 by mthiry           ###   ########.fr       */
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

static void	gnl_check(int r, int fd, char *line, t_data *data)
{
	if (r < 0)
	{
		free(line);
		close(fd);
		error_check_exit(r, "read: ", data);
	}
}

// simplified gnl that reads char by char
char	*get_next_line(int fd, t_data *data)
{
	char	buf[2];
	char	*line;
	ssize_t	r_bytes;

	line = ft_calloc(1, sizeof(char));
	alloc_check_small(line, data);
	r_bytes = 1;
	while (r_bytes > 0)
	{
		r_bytes = read(fd, buf, 1);
		buf[1] = '\0';
		gnl_check(r_bytes, fd, line, data);
		if (!r_bytes)
		{
			data->i = 0;
			break ;
		}
		line = cub_charjoin_free(line, buf[0], data);
		alloc_check_small(line, data);
		if (buf[0] == '\n')
			break ;
	}
	return (line);
}

// check whether char c is present in charset
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

// simplified atoi that checks isdigit and int max
// if there are invalid characters, set error flag set to 1
int	ft_atoi_er(const char *str, int *error)
{
	int		i;
	long	n;

	i = 0;
	n = 0;
	if (!str)
	{
		*error = 1;
		return (0);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
		{
			n = n * 10 + str[i] - '0';
			if (n > INT_MAX)
				*error = 1;
		}
		else
			*error = 1;
		i++;
	}
	return (n);
}

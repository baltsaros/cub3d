#include "cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		++i;
	return (s1[i] - s2[i]);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		i;

	i = img ->bpp - 8;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	// *(unsigned int *)dst = color;
	while (i >= 0)
	{
		if (img->endian != 0)
			*dst++ = (color >> i) & 0xFF;
		else
			*dst++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

char	*get_next_line(int fd, t_data *data)
{
	char	buf[1];
	char	*line;
	ssize_t	r_bytes;

	line = ft_calloc(1, sizeof(char));
	alloc_check_small(line, data);
	r_bytes = 1;
	buf[0] = '\0';
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
			data->i = 0;
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

int	ft_exit(t_data *data)
{
	mlx_destroy_image(data->mlx, data->ceiling.img_ptr);
	mlx_destroy_window(data->mlx, data->win);
	cub_free_all(data);
	exit(EXIT_SUCCESS);
}

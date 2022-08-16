#include "cub3d.h"

char	*cub_strjoin_free(char *rest, char *buf, t_data *data)
{
	char	*unis;
	size_t	i;
	size_t	j;

	if (!rest || !buf)
		return (0);
	data->j = ft_strlen(rest) + ft_strlen(buf) + 1;
	unis = cub_malloc(sizeof(*unis) * data->j, data);
	i = 0;
	while (rest[i])
	{
		unis[i] = rest[i];
		++i;
	}
	j = 0;
	while (buf[j])
	{
		unis[i + j] = buf[j];
		++j;
	}
	unis[j + i] = '\0';
	free(rest);
	return (unis);
}

char	*cub_charjoin_free(char *line, char b, t_data *data)
{
	size_t	i;
	char	*unis;

	i = 0;
	while (line[i])
		++i;
	unis = cub_malloc(sizeof(*unis) * (i + 2), data);
	i = 0;
	while (line[i])
	{
		unis[i] = line[i];
		++i;
	}
	unis[i] = b;
	unis[i + 1] = 0;
	free(line);
	return (unis);
}

char	*cub_strndup(char const *str, size_t size, t_data *data)
{
	char	*dest;
	size_t	i;

	dest = cub_malloc((sizeof(char) * (size + 1)), data);
	i = 0;
	while (str[i] && i < size)
	{
		dest[i] = str[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		++i;
	return (s1[i] - s2[i]);
}

void	*cub_malloc(size_t n, t_data *data)
{
	void	*ptr;

	ptr = malloc(n);
	if (!ptr)
	{
		write(2, "Cub3d: ", 7);
		write(2, "allocation failed\n", 18);
		exit(1);
	}
	return (ptr);
}

char	*cub_strdup(const char *s, t_data *data)
{
	char	*dest;
	size_t	i;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	dest = cub_malloc(sizeof(char) * (size + 1), data);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		i;

	i = img ->bpp - 8;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
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

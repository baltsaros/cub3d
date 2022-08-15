#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include "mlx_linux/mlx.h"
# include "libft/libft.h"

#define WIDTH 1000
#define HEIGHT 1000

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_map
{
	char	**raw;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
}	t_map;

typedef struct s_input
{
	size_t	i;
	size_t	j;
	char	*s_tmp;
	int		fd;
	void	*mlx;
	void	*win;
	t_img	img;
	t_map	map;
}	t_input;

//	alloc_check
void	alloc_check_big(char **str, t_input *data);
void	alloc_check_small(void *str, t_input *data);

//	utils
char	*cub_strjoin_free(char *rest, char *buf, t_input *data);
char	*cub_charjoin_free(char *line, char b, t_input *data);
char	*cub_strndup(char const *str, size_t size, t_input *data);
char	*cub_strdup(const char *s, t_input *data);
void	*cub_malloc(size_t n, t_input *data);
int		ft_strcmp(char *s1, char *s2);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
char	*get_next_line(int fd, t_input *data);

//	error_messages
int		error_check_exit(int input, char *str, t_input *data);
int		error_check_noexit(int input, char *str, t_input *data);
void	error_exit(t_input *data, char *msg);
void	check_mlx(void *mlx);
void	check_win(t_input *data);

//	hoosk
int		key_hook(int keycode, t_input *data);
int		mouse_hook(int keycode, int x, int y, t_input *data);

//	init
int		init_map(t_input *data, char *file);
t_map	read_map(t_input *data, char *file);

//	free
void	cub_free(char *str[]);
void	cub_free_all(t_input *data);

#endif
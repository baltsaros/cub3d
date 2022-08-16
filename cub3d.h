#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include "mlx/mlx.h"
# include "libft/libft.h"

#define WIDTH 1500
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

typedef struct s_data
{
	void	*mlx;
	void	*win;
	size_t	i;
	size_t	j;
	char	*s_tmp;
	int		fd;
	t_img	img;
	t_map	map;
}	t_data;

//	alloc_check
void	alloc_check_big(char **str, t_data *data);
void	alloc_check_small(void *str, t_data *data);

//	utils
char	*cub_strjoin_free(char *rest, char *buf, t_data *data);
char	*cub_charjoin_free(char *line, char b, t_data *data);
char	*cub_strndup(char const *str, size_t size, t_data *data);
char	*cub_strdup(const char *s, t_data *data);
void	*cub_malloc(size_t n, t_data *data);
int		ft_strcmp(char *s1, char *s2);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
char	*get_next_line(int fd, t_data *data);
int		check_charset(char c, char *charset);

//	error_messages
int		error_check_exit(int input, char *str, t_data *data);
int		error_check_noexit(int input, char *str, t_data *data);
void	error_exit(t_data *data, char *msg, int param);
void	check_mlx(void *mlx);
void	check_win(t_data *data);

//	hoosk
int		key_hook(int keycode, t_data *data);
int		mouse_hook(int keycode, int x, int y, t_data *data);

//	init
int		init_map(t_data *data, char *file);
t_map	read_param(t_data *data, char *file);

//	free
void	cub_free(char *str[]);
void	cub_free_all(t_data *data);
void	cub_free_params(t_data *data);

// MLX Init
void    init_mlx_and_window(t_data *data);
int 	launcher(t_data *data);

// Bresenham

#endif
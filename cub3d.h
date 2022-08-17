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

//	default window size
#define WIDTH 			1500
#define HEIGHT 			1000

// some default values
#define SQUARE_SIZE		10
#define FIELD_OF_VIEW 	2 * atan(0.66 / 1.0) = 66

//	struct to store mlx data
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_bre
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
}	t_bre;

typedef struct s_seg
{
	int x0;
	int y0;
	int	x1;
	int	y1;
}	t_seg;

typedef struct s_point
{
	int x;
	int y;
}	t_point;

//	struct to store map data
typedef struct s_map
{
	char	**raw;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	char	**f_spl;
	char	**c_spl;
	char	**map;
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
	t_img	player;
	t_map	map;
	int		pos_x;
	int		pos_y;
}	t_data;

//	alloc_check
void	alloc_check_big(char **str, t_data *data);
void	alloc_check_small(void *str, t_data *data);

//	utils_1
char	*cub_strjoin_free(char *rest, char *buf, t_data *data);
char	*cub_charjoin_free(char *line, char b, t_data *data);
char	*cub_strndup(char const *str, size_t size, t_data *data);
char	*cub_strdup(const char *s, t_data *data);
void	*cub_malloc(size_t n, t_data *data);

//	utils_2
int		ft_strcmp(char *s1, char *s2);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
char	*get_next_line(int fd, t_data *data);
int		check_charset(char c, char *charset);
int		ft_exit(t_data *data);

//	error_messages
int		error_check_exit(int input, char *str, t_data *data);
int		error_check_noexit(int input, char *str, t_data *data);
void	error_exit(t_data *data, char *msg, int param);
void	check_mlx(void *mlx, t_data *data);
void	check_win(t_data *data);

//	hooks
int		key_hook(int keycode, t_data *data);
int		mouse_hook(int keycode, int x, int y, t_data *data);
int		infinite_hook(int keycode, t_data *data);

//	init
void	init_vars(t_data *data);
void	check_extension(t_data *data, char *file);
t_map	read_param(t_data *data, char *file);
void	check_param(t_map *map, t_data *data);
int		init_map(t_data *data, char *file);

//	init_utils_1 - for check_param
char	*find_param(char **raw, char *param, t_data *data);
size_t	find_mapsize(char **raw, int j);
void	copy_map(char **raw, t_data *data);

//	init_utils_2 - for check_map
void	check_chars(char **raw, t_data *data);
void	check_rows(char **map, t_data *data);
size_t	check_length(char **map, size_t i, t_data *data);
void	check_columns(char **map, t_data *data);
void	check_map(t_map *map, t_data *data);

//	free
void	cub_free(char *str[]);
void	cub_free_all(t_data *data);
void	cub_free_params(t_data *data);

// Launcher
void    init_mlx_and_window(t_data *data);
int 	launcher(t_data *data);

// Launcher Utils
int		create_trgb(int t, int r, int g, int b);

// Draw All
void    init_background(t_data *data);
void    draw_player(t_data *data);
void    draw_all(t_data *data);

// Bresenham
void	bresenham(t_point begin, t_point end, t_img *img);

#endif
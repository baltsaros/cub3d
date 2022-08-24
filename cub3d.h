#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include <stdint.h>
# include "mlx_linux/mlx.h"
# include "libft/libft.h"

//	default window size
# define WIDTH 800
# define HEIGHT 600

# define RED 0xFF0000
# define GREEN 0xFF00
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define GRAY 0x808080

# define PI 3.1415926535
# define FOV 60

//	struct to store mlx data for map
typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

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
	int		dir;
	size_t	width;
	size_t	height;
}	t_map;

//	global(integral) struct to store all data
typedef struct s_input
{
	size_t	i;
	size_t	j; 
	char	*s_tmp;
	int		fd;
	void	*mlx;
	void	*win;
	int		pcoord[2];
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pa;
	int		psize;
	float	sx;
	float	sy;
	int		color;
	t_img	img;
	t_img	pl;
	t_img	ray;
	t_map	map;
}	t_input;

//	alloc_check
void	alloc_check_big(char **str, t_input *data);
void	alloc_check_small(void *str, t_input *data);

//	utils_1
char	*cub_strjoin_free(char *rest, char *buf, t_input *data);
char	*cub_charjoin_free(char *line, char b, t_input *data);
char	*cub_strndup(char const *str, size_t size, t_input *data);
char	*cub_strdup(const char *s, t_input *data);
void	*cub_malloc(size_t n, t_input *data);

//	utils_2
int		ft_strcmp(char *s1, char *s2);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
char	*get_next_line(int fd, t_input *data);
int		check_charset(char c, char *charset);
int		ft_exit(t_input *data);

//	error_messages
int		error_check_exit(int input, char *str, t_input *data);
int		error_check_noexit(int input, char *str, t_input *data);
void	error_exit(t_input *data, char *msg, int param);
void	check_mlx(void *mlx, t_input *data);
void	check_win(t_input *data);

//	hooks
int		is_wall(t_input *data, char **map);
int		key_hook(int keycode, t_input *data);
int		mouse_hook(int keycode, int x, int y, t_input *data);

//	init
void	init_vars(t_input *data);
void	check_extension(t_input *data, char *file);
t_map	read_param(t_input *data, char *file);
void	check_param(t_map *map, t_input *data);
int		init_map(t_input *data, char *file);

//	init_utils_1 - for check_param
char	*find_param(char **raw, char *param, t_input *data);
size_t	find_mapsize(char **raw, int j);
void	copy_map(char **raw, t_input *data);

//	init_utils_2 - for check_map
void	check_chars(char **raw, t_input *data);
void	check_rows(char **map, t_input *data);
size_t	check_length(char **map, size_t i, t_input *data);
void	check_columns(char **map, t_input *data);
void	check_map(t_map *map, t_input *data);

//	free
void	cub_free(char *str[]);
void	cub_free_all(t_input *data);
void	cub_free_params(t_input *data);

//	drawing
int		encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
int		render(t_input *data);
void	render_map(t_input *data, char **map);
void	render_elem(t_input *data, int color, int j, int i);
void	render_player(t_input *data, t_img *img);
void	render_ray(t_input *data, int color);

#endif
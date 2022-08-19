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
	int		basic_color;
}	t_img;

// structs to store values for drawing

typedef struct s_bre
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
}	t_bre;

typedef struct s_point
{
	int x;
	int y;
}	t_point;

typedef struct s_seg
{
	t_point	p0;
	t_point	p1;
}	t_seg;

// 	struct for positions
typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	pos_win_x;
	float	pos_win_y;
	float	p_ang;
	float	delta_x;
	float	delta_y;
	t_img	player;
}	t_player;

typedef struct s_ray
{
	int test;
	t_img		ray;
}	t_ray;

typedef struct s_minimap
{
	t_point		position;
	int			width;
	int			height;
	t_img		minimap;
}	t_minimap;

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
	size_t	width;
	size_t	height;
}	t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	size_t		i;
	size_t		j;
	char		*s_tmp;
	int			fd;
	int			size_player;
	int			size_square;
	t_img		ceiling;
	t_map		map;
	t_player	player_s;
	t_ray		ray_s;
	t_minimap	minimap_s;
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
int		key_hook_manager(int keycode, t_data *data);
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
void    hook_manager(t_data *data);
int 	launcher(t_data *data);

// Draw All
void    draw_square(t_img img, int color, int end_i, int end_j);
void    init_ceiling(t_data *data);
void    draw_all(t_data *data);

// Minimap
void    draw_square_coord(t_data *data, int color, int x, int y);
void    draw_empty_square_coord(t_data *data, int color, int x, int y);
void    draw_map(t_data *data, int color, int height, int width);
void    redraw_map(t_data *data, int color, int height, int width);
void    init_minimap(t_data *data, t_minimap minimap);
void    init_minimap_values(t_data *data);

// Player
void    init_player(t_data *data);
void    init_player_values(t_data *data);

// Ray
void  draw_ray(t_data *data);
void  init_ray(t_data *data);

// Bresenham
void	mlx_pixel_put_img(t_img	*img, int x, int y, int color);
void	init_bre_values(t_bre	*values, t_seg *seg);
void	ft_put_pixel(t_data *data, t_seg *seg, t_img *img, int color);
void	init_seg_values(t_seg *seg, t_point *begin, t_point *end);
void	bresenham(t_data *data, t_point begin, t_point end, t_img *img);

// Calculs Utils
int		create_trgb(int t, int r, int g, int b);
float   degToRad(int a);
int 	FixAng(int a);

#endif
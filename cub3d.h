/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:11:16 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/17 18:43:32 by mthiry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/* Default Window Size */
# define WIDTH			1500
# define HEIGHT 		1000

/* Default Player Values */
# define SQUARE_SIZE	64
# define PLAYER_SIZE	8
# define FIELD_OF_VIEW 	60

/* North-South-East-West Flags */
# define NORTH			1
# define SOUTH			2
# define EAST			3
# define WEST			4
# define ERROR_POS		100

/* Hooks Values */
# define KEYPRESS		2
# define KEYRELEASE		3
# define MOUSEMOVE		6
# define DESTROY		17
# define KEYPRESSMASK	1L
# define KEYRELEASEMASK	2L
# ifdef __linux__

enum	e_s_keys
{
	LEFT	= 65361,
	RIGHT	= 65363,
	W		= 119,
	A		= 97,
	S		= 115,
	D		= 100,
	ESC		= 65307
};
# else

enum	e_s_keys
{
	LEFT	= 124,
	RIGHT	= 123,
	W		= 13,
	A		= 0,
	S		= 1,
	D		= 2,
	ESC		= 53
};
# endif

/* Structs to store mlx data for map */
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		basic_color;
}	t_img;

typedef struct s_text
{
	t_img	img;
	int		width;
	int		height;
}	t_text;

/* Structs to store utils values for drawing */
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_ray_calcul
{
	int		r;
	int		mx;
	int		my;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	disv;
	float	dish;
	float	vx;
	float	vy;
	int		ipx;
	int		ipx_add_xo;
	int		ipx_sub_xo;
	int		ipy;
	int		ipy_add_yo;
	int		ipy_sub_yo;
}	t_ray_calcul;

typedef struct s_wall_drawing
{
	float	distproj;
	float	wallheight;
	float	ty;
	float	ty_step;
	float	tx;
	t_point	begin;
	t_point	end;
}	t_wall_drawing;

/* Structs for player and minimap positions */
typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	pos_win_x;
	float	pos_win_y;
	float	p_ang;
	float	delta_x;
	float	delta_y;
	int		speed;
	int		rot_speed;
}	t_player;

typedef struct s_minimap
{
	t_point		position;
	int			width;
	int			height;
}	t_minimap;

/* Struct for keys */
typedef struct s_keyboard
{
	int	esc;
	int	w;
	int	a;
	int	s;
	int	d;
	int	right;
	int	left;
}	t_keyboard;

/* Struct for map values */
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
	int		coord[2];
	int		dir;
	int		angle;
	size_t	width;
	size_t	height;
}	t_map;

/* Basic struct for basic data */
typedef struct s_data
{
	void			*mlx;
	void			*win;
	size_t			i;
	size_t			j;
	int				x;
	char			*s_tmp;
	int				fd;
	t_img			background;
	t_map			map;
	t_player		player_s;
	t_img			player;
	t_minimap		minimap_s;
	t_img			minimap;
	t_img			walls;
	t_ray_calcul	ray_calcul;
	t_wall_drawing	wall_drawing;
	t_text			no_text;
	t_text			so_text;
	t_text			ea_text;
	t_text			we_text;
	int				is_full_screen;
	t_keyboard		keyboard;
}	t_data;

/* ************************************************************************** */
/*                                                                            */
/*		Functions and files                                                   */
/*                                                                            */
/* ************************************************************************** */

/* alloc_check.c */
void	alloc_check_big(char **str, t_data *data);
void	alloc_check_small(void *str, t_data *data);

/* calculs_utils.c */
float	degtorad(float a);
float	fixang(float a);

/* cub_free.c */
void	cub_free(char *str[]);
void	cub_free_params(t_data *data);
void	cub_free_all(t_data *data);

/* cub_utils_1.c */
char	*cub_strjoin_free(char *rest, char *buf, t_data *data);
char	*cub_charjoin_free(char *line, char b, t_data *data);
char	*cub_strndup(char const *str, size_t size, t_data *data);
void	*cub_malloc(size_t n, t_data *data);
char	*cub_strdup(const char *s, t_data *data);

/* cub_utils_2.c */
int		ft_strcmp(char *s1, char *s2);
char	*get_next_line(int fd, t_data *data);
int		check_charset(char c, char *charset);

/* cub3d.c */
void	hook_manager(t_data *data);
int		launcher(t_data *data);

/* draw_all.c */
void	init_background(t_data *data);
int		draw_all(t_data *data);

/* draw_utils.c */
int		create_trgb(int t, int r, int g, int b);
int		get_pixel(t_img img, int y, int x);
void	mlx_pixel_put_img(t_img	*img, int x, int y, int color);
void	draw_square(t_img img, int color, int end_i, int end_j);
void	draw_square_from(t_img img, int color, t_point begin, t_point end);

/* draw_wall.c */
void	draw_a_wall(t_data *data, t_wall_drawing *wall,
			t_text text, double shade);
void	draw_vertical_line(t_data *data, t_wall_drawing *wall,
			t_ray_calcul *ray, int pos);
void	init_calculate_wall(t_data *data, t_ray_calcul *ray, int pos);

/* error_messages.c */
int		error_check_exit(int input, char *str, t_data *data);
int		error_check_noexit(int input, char *str, t_data *data);
void	error_exit(t_data *data, char *msg, int param);
void	check_mlx(void *mlx, t_data *data);
void	check_win(t_data *data);

/* exit.c */
int		ft_exit(t_data *data);
void	leave(t_data *data, int ret);

/* hooks.c */
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
void	rotate_fov(int keycode, t_data *data);
int		mouse_hook(int x, int y, t_data *data);
int		key_hook_manager(t_data *data);

/* horizontal_wall.c */
float	dish_calcul(t_data *data, float ra, float ry, float rx);
void	calculate_horizontal_distance(t_data *data, t_ray_calcul *ray, int dof);
int		check_up(t_data *data, t_ray_calcul *ray, float Tan);
int		check_down(t_data *data, t_ray_calcul *ray, float Tan);
int		check_horizontal_wall(t_data *data, t_ray_calcul *ray, float Tan);

/* init_img.c */
int		init_img(t_data *data);
int		is_xpm(char *str);
int		load_textures(t_data *data);

/* init_map_utils_1.c */
void	check_chars(char **raw, t_data *data);
char	*find_param(char **raw, char *param, t_data *data);
void	find_mapsize(char **raw, int j, t_data *data);
void	copy_map(char **raw, t_data *data);
void	check_map(t_map *map, t_data *data);

/* init_map_utils_2.c */
int		check_wall(char c, int state);
void	check_gap(char **map, size_t i, size_t j, t_data *data);
void	check_rows(char **map, t_data *data);
void	check_columns(char **map, t_data *data);
void	check_player(char **map, t_data *data);

/* init_map_utils_3.c */
void	check_direction(t_data *data);
void	print_map(t_data *data, char **map);

/* init_map.c */
void	init_vars(t_data *data);
void	check_extension(t_data *data, char *file);
void	check_param(t_map *map, t_data *data);
t_map	read_param(t_data *data, char *file);
int		init_map(t_data *data, char *file);

/* minimap.c */
void	draw_square_coord(t_data *data, int color, int x, int y);
void	draw_map(t_data *data, int color, int height, int width);
void	init_minimap_values(t_data *data);

/* move_utils.c */
void	collisions_calculs_up_down(t_data *data, t_ray_calcul *collisions);
void	collisions_calculs_right(t_data *data, t_ray_calcul *collisions);
void	collisions_calculs_left(t_data *data, t_ray_calcul *collisions);

/* move.c */
void	move_up(t_data *data, t_ray_calcul *collisions);
void	move_down(t_data *data, t_ray_calcul *collisions);
void	move_right(t_data *data, t_ray_calcul *collisions);
void	move_left(t_data *data, t_ray_calcul *collisions);

/* player.c */
int		is_player(char c);
void	init_player_pos(t_data *data, int height, int width);
void	init_player_values(t_data *data);

/* ray.c */
int		adapt_distance(t_ray_calcul *ray, int posH, int posV);
void	fisheye_fix(t_data *data, t_ray_calcul *ray);
void	raycast(t_data *data, t_ray_calcul ray);

/* vertical_wall.c */
float	disv_calcul(t_data *data, float ra, float ry, float rx);
void	calculate_vertical_distance(t_data *data, t_ray_calcul *ray, int dof);
int		check_right(t_data *data, t_ray_calcul *ray, float Tan);
int		check_left(t_data *data, t_ray_calcul *ray, float Tan);
int		check_vertical_wall(t_data *data, t_ray_calcul *ray, float Tan);

#endif

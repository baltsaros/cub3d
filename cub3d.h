/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuzdin <abuzdin@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:11:16 by mthiry            #+#    #+#             */
/*   Updated: 2022/11/30 07:58:42 by abuzdin          ###   ########.fr       */
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
# include "libft/libft.h"
# ifdef __linux__
#  include "mlx_linux/mlx.h"
# else
#  include "mlx/mlx.h"
# endif

/* Default Window Size */
# define WIDTH			1500
# define HEIGHT 		1000

/* Default Player Values */
# define SQUARE_SIZE	64
# define PSIZE	8
# define FIELD_OF_VIEW 	60

/* North-South-East-West Flags */
enum e_pos_flags
{
	NORTH			= 1,
	SOUTH			= 2,
	EAST			= 3,
	WEST			= 4,
	UNDEFINED		= 100
};

/* Errors flags */
enum e_errors
{
	ERROR_IMG_PTR	= 2,
	ERROR_TEXT_PTR	= 3,
	ERROR_BAD_EXT	= 4,
	ERROR_FAILED_M	= 5
};

/* Mlx events and masks for hooks */
enum e_hooks
{
	KEYPRESS		= 2,
	KEYRELEASE		= 3,
	MOUSEMOVE		= 6,
	DESTROY			= 17,
	KEYPRESSMASK	= 1L,
	KEYRELEASEMASK	= 2L,
	BUTTONMOTION	= 1L<<13,
	STRUCTURENOT	= 1L<<17
};

/* Keycodes for Linux and (if not) Mac*/
# ifdef __linux__

enum	e_s_keys
{
	LEFT	= 65363,
	RIGHT	= 65361,
	W		= 119,
	A		= 97,
	S		= 115,
	D		= 100,
	ESC		= 65307,
	SPACE	= 32,
	SHIFT	= 65505
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
	ESC		= 53,
	SPACE	= 49,
	SHIFT	= 257
};
# endif

/* Set of colors */
enum	e_colors {
	RED		= 0xFF0000,
	GREEN	= 0x00FF00,
	WHITE	= 0xFFFFFF,
	BLACK	= 0x000000,
	GRAY	= 0x808080,
	YELLOW	= 0xFFFF00,
	DPURPLE = 0x301934,
	TEST	= 0x90B3B0
};

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

typedef struct s_fpoint
{
	float	x;
	float	y;
}	t_fpoint;

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
	int		is_door_v;
	int		is_door_h;
	int		is_sprite_v;
	int		is_sprite_h;
}	t_ray_calcul;

typedef struct s_wall_drawing
{
	float	distproj;
	float	wallheight;
	float	ty;
	float	ty_step;
	float	tx;
	float	tx_step;
	t_point	begin;
	t_point	end;
}	t_wall_drawing;

/* struct for objects */
typedef struct s_object
{
	t_fpoint	fpos;
	t_point		pos;
	t_fpoint	fdis;
	float		distance;
	float		tmp;
	float		q;
	float		b;
	t_fpoint	screen;
}	t_object;

/* struct for storing value for quicksort */
typedef struct s_quicksort
{
	int			i;
	int			j;
	int			pivot;
	t_object	tmp;
}	t_quicksort;

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
	t_fpoint	position;
	char		**mmap;
	int			width;
	int			height;
	float		step;
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
	int	shift;
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
	int		floor[3];
	int		ceiling[3];
	char	**map;
	int		coord[2];
	int		door[2];
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
	int				door;
	size_t			i;
	size_t			j;
	int				x;
	int				old_x;
	char			*s_tmp;
	int				fd;
	t_map			map;
	t_player		player_s;
	t_minimap		minimap_s;
	t_img			minimap;
	t_img			walls;
	t_ray_calcul	ray_calcul;
	t_wall_drawing	wall_drawing;
	t_text			no_text;
	t_text			so_text;
	t_text			ea_text;
	t_text			we_text;
	t_text			door_text;
	t_text			sprite_1;
	t_text			sprite_2;
	t_text			sprite_3;
	t_keyboard		keyboard;
	int				anim;
	int				*depth;
	int				is_depth_allocated;
	int				nb_objs;
	t_object		*objs;
	int				is_objs_allocated;
	t_quicksort		quick;
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
int		ft_atoi_er(const char *str, int *error);

/* cub3d.c */
void	hook_manager(t_data *data);
int		launcher(t_data *data);

/* door.c */
int		is_close(t_data *data, int my, int mx);
int		close_door(t_data *data, int my, int mx);
int		is_door_opened(t_data *data, t_ray_calcul *ray);
int		is_door_closed(t_data *data, t_ray_calcul *ray);
void	open_close_door(t_data *data, t_ray_calcul ray);

/* draw_all.c */
void	init_background(t_data *data);
int		draw_all(t_data *data);

/* draw_sprites.c */
void	draw_sprite_y(t_data *data, t_text text, t_wall_drawing *wall);
void	draw_sprite_x(t_data *data, t_text text, t_wall_drawing *wall,
			t_object *obj);
void	init_draw_sprite(t_data *data, t_object	*obj, t_wall_drawing *wall);

/* draw_utils.c */
int		create_trgb(int t, int r, int g, int b);
int		get_pixel(t_img img, int y, int x);
void	mlx_pixel_put_img(t_img	*img, int x, int y, int color);
void	draw_square(t_img img, int color, int end_i, int end_j);
void	draw_square_from(t_img img, int color, t_point begin, t_point end);

/* draw_wall_utils.c */
float	dis_calcul(t_data *data, float ra, float ry, float rx);
int		is_within_maps(int my, int mx, int height, int width);
int		is_wall(char c);

/* draw_wall.c */
void	draw_a_wall(t_data *data, t_wall_drawing *wall,
			t_text text);
void	draw_vertical_line(t_data *data, t_wall_drawing *wall,
			t_ray_calcul *ray, int pos);
void	draw_vertical_door(t_data *data, t_wall_drawing *wall,
			t_ray_calcul *ray, int pos);
void	init_calculate_wall(t_data *data, t_ray_calcul *ray, int pos);

/* error_messages.c */
int		error_check_exit(int input, char *str, t_data *data);
int		error_check_noexit(int input, char *str);
void	error_exit(t_data *data, char *msg, int param);
void	check_mlx(void *mlx, t_data *data);
void	check_win(t_data *data);

/* error.c */
void	check_errors(t_data *data, int ret);

/* exit.c */
void	free_images(t_data *data);
int		ft_exit(t_data *data);
void	leave(t_data *data, int ret);

/* hooks.c */
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
void	rotate_fov(int keycode, t_data *data);
int		key_hook_manager(t_data *data);

/* horizontal_wall.c */
void	calculate_horizontal_distance(t_data *data, t_ray_calcul *ray,
			int index);
int		check_up(t_data *data, t_ray_calcul *ray, float Tan);
int		check_down(t_data *data, t_ray_calcul *ray, float Tan);
int		check_horizontal_wall(t_data *data, t_ray_calcul *ray, float Tan);

/* init_img.c */
void	init_img_null(t_data *data);
int		init_img(t_data *data);
int		is_xpm(char *str);
void	mlx_xpm_init(t_data *data);
int		load_textures(t_data *data);

/* init_map_utils_1.c */
void	check_chars(char **raw, t_data *data);
size_t	check_lines(char **map, size_t j, t_data *data);
void	find_mapsize(char **raw, int j, t_data *data);
void	copy_map(char **raw, t_data *data);
void	check_map(t_map *map, t_data *data);

/* init_map_utils_2.c */
int		check_wall(char c, int state);
void	check_gap(char **map, size_t i, size_t j, t_data *data);
void	check_door(char **map, size_t i, size_t j, t_data *data);
void	check_rows(char **map, t_data *data);
void	check_columns(char **map, t_data *data);

/* init_map_utils_3.c */
void	check_player(char **map, t_data *data);
void	check_direction(t_data *data);
void	check_num(char **str, int *array, t_data *data);
void	check_colors(t_map *map, t_data *data);
void	print_map(t_data *data, char **map);

/* init_map_utils_4.c */
char	*find_param(char **raw, char *param, t_data *data);
char	*find_param_color(char **raw, char *param, t_data *data);
size_t	skip_wspace(char **map, size_t j, size_t i);

/* init_map.c */
void	init_vars(t_data *data);
void	check_extension(t_data *data, char *file);
void	check_param(t_map *map, t_data *data);
t_map	read_param(t_data *data, char *file);
int		init_map(t_data *data, char *file);

/* init_sprites.c */
int		init_nbr_objs(t_data *data);
void	init_obj_pos(t_data *data);
void	draw_sprites(t_data *data);
int		init_sprites(t_data *data);

/* minimap.c */
void	draw_square_coord(t_data *data, int color, int x, int y);
void	draw_mm_background(t_data *data, int color);
void	draw_dir(t_data *data, int color);
void	draw_map(t_data *data, char **map, int color);
void	init_minimap(t_data *data);

/* minimap_utils.c */
void	init_minimap_values(t_data *data);
char	*memcpy_offset(void *dest, const void *src, size_t n, size_t offset);

/* mouse_hooks.c */
int		mouse_hook(int x, int y, t_data *data);
void	mouse_management(t_data *data);

/* move_utils.c */
void	collisions_calculs_up_down(t_data *data, t_ray_calcul *collisions);
void	collisions_calculs_right(t_data *data, t_ray_calcul *collisions);
void	collisions_calculs_left(t_data *data, t_ray_calcul *collisions);
double	set_mult(t_data *data, int dir);

/* move.c */
void	move_up(t_data *data, t_ray_calcul *collisions, double mult);
void	move_down(t_data *data, t_ray_calcul *collisions, double mult);
void	move_right(t_data *data, t_ray_calcul *collisions, double mult);
void	move_left(t_data *data, t_ray_calcul *collisions, double mult);
void	move(t_data *data);

/* player.c */
int		is_player(char c);
void	init_player_values(t_data *data);

/* quicksort.c */
void	quicksort_2(t_data *data, t_quicksort quick, int first, int last);
void	quicksort(t_data *data, t_quicksort quick, int first, int last);

/* ray.c */
int		adapt_distance(t_ray_calcul *ray, int posH, int posV);
void	fisheye_fix(t_data *data, t_ray_calcul *ray);
void	raycast(t_data *data, t_ray_calcul ray);

/* sprites.c */
int		load_sprites_textures(t_data *data);
int		init_depth(t_data *data);
void	draw_a_sprite(t_data *data, t_object obj);

/* vertical_wall.c */
void	calculate_vertical_distance(t_data *data, t_ray_calcul *ray, int index);
int		check_right(t_data *data, t_ray_calcul *ray, float Tan);
int		check_left(t_data *data, t_ray_calcul *ray, float Tan);
int		check_vertical_wall(t_data *data, t_ray_calcul *ray, float Tan);

#endif

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <libft.h>
# include <mlx.h>
# include <errno.h>
# include <math.h>

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

typedef struct s_input
{
	size_t	i;
	size_t	j;
	char	*s_tmp;
	void	*mlx;
	void	*win;
	t_img	img;
}	t_input;

//	utils
char	*cub_strjoin_free(char *rest, char *buf, t_input *data);
char	*cub_charjoin_free(char *line, char b, t_input *data);
char	*cub_strndup(char const *str, size_t size, t_input *data);
char	*cub_strdup(const char *s, t_input *data);
void	*cub_malloc(size_t n, t_input *data);
int		ft_strcmp(char *s1, char *s2);

//	error_messages
int		error_check_exit(int input, char *str, t_input *data);
int		error_check_noexit(int input, char *str, t_input *data);


//	init

//	free
void	cub_free(char *str[]);

#endif
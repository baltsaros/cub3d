C_PURPLE_B		=\033[1;95m
C_YELLOW_B		=\033[1;33m
C_RED_B			=\033[1;31m
C_WHITE			=\033[0;97m
C_GREEN			=\033[0;32m
C_GREEN_B		=\033[1;32m
C_RESET			=\033[0m

OS			= $(shell uname -s)
GCC			= gcc
RM			= rm -f
RMF			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -g

NAME		= cub3d
LIBFT		= ./libft/libft.a
MLX			= -Lmlx -lmlx -framework OpenGL -framework AppKit
HOOKS		= hooks_mac.c
INCS		= -Ilibft -Imlx

ifeq	($(OS), Linux)
$(warning $(OS))
		MLX 	= -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz
		HOOKS	= hooks.c
		INCS	= -Ilibft -Imlx_linux
endif
#-lmlx_Linux

SRCS		=	cub3d.c \
				cub_utils_1.c \
				cub_utils_2.c \
				cub_free.c \
				alloc_check.c \
				error_messages.c \
				$(HOOKS) \
				init_map.c \
				init_map_utils_1.c \
				init_map_utils_2.c \
				init_map_utils_3.c \
				draw_all.c \
				minimap.c \
				player.c \
				ray.c \
				vertical_wall.c \
				horizontal_wall.c \
				draw_wall.c \
				calculs_utils.c \
				draw_utils.c \
				init_img.c \
				move.c \
				collisions.c

HEADER		= cub3d.h

OBJ_DIR		= objs
OBJ_FILES	= $(SRCS:.c=.o)
OBJS		= $(addprefix $(OBJ_DIR)/,$(OBJ_FILES))

all:		libft $(NAME)

$(OBJ_DIR)/%.o: %.c
			@mkdir -p $(OBJ_DIR)
			@printf "$(C_GREEN).$(C_RESET)";
			@$(GCC) $(CFLAGS) -c $< $(INCS) -o $@

$(NAME):	$(OBJS) $(HEADER)
			@$(GCC) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)
			@printf "\n$(C_GREEN_B)Finished!$(C_RESET)\n";

libft:
			@make -C ./libft

norm:
			@echo "$(C_PURPLE_B)Let's test the Norm!$(C_RESET)";
			@norminette
			@echo "$(C_PURPLE_B)Done!$(C_RESET)";

clean:
			@echo "$(C_RED_B)Deleting cub3d o-files...$(C_RESET)";
			@make -C ./libft clean
			@$(RM) $(OBJS)
			@$(RMF) $(OBJ_DIR)
			@echo "$(C_RED_B)Cub3d o-files have been deleted!$(C_RESET)";

fclean:		clean
			@make -C ./libft fclean
			@echo "$(C_RED_B)Deleting cub3d program...$(C_RESET)";
			@$(RM) $(NAME)
			@echo "$(C_RED_B)Cub3d program has been deleted!$(C_RESET)";

re:			fclean all

val:		${NAME}
			valgrind --leak-check=full ./$(NAME)

.PHONY:		all clean fclean libft re .c.o norm brew val mlx

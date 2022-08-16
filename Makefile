C_PURPLE_B		=\033[1;95m
C_YELLOW_B		=\033[1;33m
C_RED_B			=\033[1;31m
C_WHITE			=\033[0;97m
C_GREEN			=\033[0;32m
C_GREEN_B		=\033[1;32m
C_RESET			=\033[0m

GCC			= gcc
RM			= rm -f
RMF			= rm -rf
CFLAGS		= -Wall -Wextra -Werror

NAME		= cub3d
LIBFT       = ./libft/libft.a
MLX			= ./mlx/libmlx.a
SRCS		=	cub3d.c \
				cub_utils_1.c \
				cub_utils_2.c \
				cub_free.c \
				alloc_check.c \
				error_messages.c \
				hooks.c \
				init_map.c \
				bresenham.c \
				launcher.c \
				launcher_utils.c \
				draw_all.c \
				init_map_utils_1.c \
				init_map_utils_2.c

OBJ_DIR		= objs
OBJ_FILES	= $(SRCS:.c=.o)
OBJS		= $(addprefix $(OBJ_DIR)/,$(OBJ_FILES))

INCS		= -Ilibft -Imlx

all:		libft $(NAME)

$(OBJ_DIR)/%.o: %.c
			@mkdir -p $(OBJ_DIR)
			@printf "$(C_GREEN).$(C_RESET)";
			@$(GCC) $(CFLAGS) -c $< $(INCS) -o $@

$(NAME):	$(OBJS) $(MLX)
			@$(GCC) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit ${INCS} libft/libft.a -o $(NAME)
			@printf "\n$(C_GREEN_B)Finished!$(C_RESET)\n";

libft:
			@make -C ./libft

$(MLX):
			@make -C ./mlx/

norm:
			@echo "$(C_PURPLE_B)Let's test the Norm!$(C_RESET)";
			@norminette
			@echo "$(C_PURPLE_B)Done!$(C_RESET)";

clean:
			@echo "$(C_RED_B)Deleting cub3d o-files...$(C_RESET)";
			@make -C ./libft clean
			@$(RM) $(OBJS)
			@$(RMF) $(OBJ_DIR)
			@$(RM) ./mlx/*.o
			@echo "$(C_RED_B)Cub3d o-files have been deleted!$(C_RESET)";

fclean:		clean
			@make -C ./libft fclean
			@echo "$(C_RED_B)Deleting cub3d program...$(C_RESET)";
			@$(RM) $(NAME) $(MLX)
			@echo "$(C_RED_B)Cub3d program has been deleted!$(C_RESET)";

re:			fclean all

val:		${NAME}
			valgrind --leak-check=full ./$(NAME)

.PHONY:		all clean fclean libft re .c.o norm brew val mlx

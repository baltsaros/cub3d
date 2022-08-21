C_PURPLE_B		=\033[1;95m
C_YELLOW_B		=\033[1;33m
C_RED_B			=\033[1;31m
C_WHITE			=\033[0;97m
C_GREEN			=\033[0;32m
C_GREEN_B		=\033[1;32m
C_RESET			=\033[0m

NAME		= cub3d

# SRC_DIR		= srcs
SRCS		= cub3d.c \
				cub_free.c \
				cub_utils_1.c \
				cub_utils_2.c \
				alloc_check.c \
				error_messages.c \
				hooks.c \
				drawing.c \
				init_map.c \
				init_map_utils_1.c \
				init_map_utils_2.c

# SRCS		= $(notdir $(SRC_FILES))

OBJ_DIR		= objs
OBJ_FILES	= $(SRCS:.c=.o)
OBJS		= $(addprefix $(OBJ_DIR)/,$(OBJ_FILES))

INCS		= -Ilibft -Imlx_linux

GCC			= gcc
RM			= rm -f
RMF			= rm -rf
CFLAGS		= -Wall -Wextra -Werror

all:		libft $(NAME)

$(OBJ_DIR)/%.o: %.c
			@mkdir -p $(OBJ_DIR)
			@printf "$(C_GREEN).$(C_RESET)";
			@$(GCC) $(CFLAGS) -c $< $(INCS) -o $@

$(NAME):	$(OBJS) 
			@$(GCC) $(OBJS) -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz libft/libft.a -o $(NAME)
			@printf "\n$(C_GREEN_B)Finished!$(C_RESET)\n";


libft:
			@make -C ./libft

norm:
			@echo "$(C_PURPLE_B)Let's test the Norm!$(C_RESET)";
			@norminette
			@echo "$(C_PURPLE_B)Done!$(C_RESET)";

clean:
			@echo "$(C_RED_B)Deleting $(NAME) o-files...$(C_RESET)";
			@make -C ./libft clean
			@$(RM) $(OBJS)
			@$(RMF) $(OBJ_DIR)
			@echo "$(C_RED_B)Cub3d o-files have been deleted!$(C_RESET)";

fclean:		clean
			@make -C ./libft fclean
			@echo "$(C_RED_B)Deleting $(NAME) program...$(C_RESET)";
			@$(RM) $(NAME)
			@echo "$(C_RED_B)Cub3d program has been deleted!$(C_RESET)";

re:			fclean all

val:		libft ${NAME}
			valgrind --leak-check=full ./$(NAME)

.PHONY:		all clean fclean libft re .c.o norm val

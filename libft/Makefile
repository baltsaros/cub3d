C_PURPLE_B		=\033[1;95m
C_YELLOW_B		=\033[1;33m
C_RED_B			=\033[1;31m
C_WHITE			=\033[0;97m
C_GREEN			=\033[0;32m
C_GREEN_B		=\033[1;32m
C_RESET			=\033[0m

NAME	= libft.a

SRC_DIR		= .
SRC_FILES	= ${shell find ${SRC_DIR} -name '*.c'}
SRCS		= ${notdir ${SRC_FILES}}

OBJ_DIR		= objs
OBJ_FILES	= ${SRCS:.c=.o}
OBJS		= ${addprefix ${OBJ_DIR}/,${OBJ_FILES}}

INCS	= -I .

LIB		= ar rcs
GCC		= gcc
RM		= rm -f
RMF		= rm -rf
CFLAGS	= -Wall -Wextra -Werror

all:		${NAME}

${OBJ_DIR}/%.o : %.c
			@mkdir -p ${OBJ_DIR}
			@printf "${C_GREEN}.${C_RESET}";
			@${GCC} ${CFLAGS} -c $< ${INCS} -o $@

# @echo "${C_YELLOW_B}Compiling libft...${C_RESET}";

${NAME}:	${OBJS}
			@${LIB} ${NAME} ${OBJS} 
			@printf "\n${C_GREEN_B}Libft has been compiled!${C_RESET}\n";

norm:
			@echo "${C_PURPLE_B}Let's check the Norm!${C_RESET}";
			@norminette
			@echo "${C_PURPLE_B}Done!${C_RESET}";
clean:
			@echo "${C_RED_B}Deleting libft o-files...${C_RESET}";
			@${RM} ${OBJS}
			@${RMF} ${OBJ_DIR}
			@echo "${C_RED_B}Libft o-files have been deleted!${C_RESET}";

fclean:		clean
			@echo "${C_RED_B}Deleting libft library...${C_RESET}";
			@${RM} ${NAME}
			@echo "${C_RED_B}Libft library has been deleted!${C_RESET}";

re:			fclean all

.PHONY:		all clean fclean re .c.o norm
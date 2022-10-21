RED = \033[0;31m
NC = \033[0m	
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m

NAME = cub3D

CC = gcc
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit 
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
INCFLAG = -I./includes

SRCS = ./main.c ./srcs/parser.c ./srcs/utils/ErrorMessage.c ./srcs/utils/ft_strchr.c  \
./srcs/utils/ft_strncmp.c ./srcs/utils/ft_split.c ./srcs/utils/ft_strjoin.c ./srcs/utils/ft_strlen.c \
./srcs/utils/getnextline.c ./srcs/utils/freeArray.c ./srcs/utils/ft_isspace.c ./srcs/utils/ft_substr.c \
./srcs/utils/ft_strdup.c ./srcs/constructor.c ./srcs/lstUtils/ft_lstadd_back.c ./srcs/lstUtils/ft_lstadd_front.c \
./srcs/lstUtils/ft_lstdelete.c ./srcs/lstUtils/ft_lstlast.c ./srcs/lstUtils/ft_lstnew.c ./srcs/lstUtils/ft_lstsize.c \
./srcs/lstUtils/ft_lstprint.c ./srcs/utils/ft_atoi.c ./srcs/utils/ft_strisdigit.c ./srcs/isMapValid.c\
./srcs/draw_map.c ./srcs/win_utils/closeWin.c ./srcs/movePlayer.c ./srcs/hooks_handler.c ./srcs/utils/drawing_utils.c \
./srcs/utils/ft_memcpy.c

all : $(NAME)

$(NAME) :
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(SRCS) $(INCFLAG) -o $(NAME)
	# rm -rf $(NAME).dSYM
	@echo "$(CYAN)\n====== $(NAME) compiling finished ======"
	@echo "==========================================${NC}\n"

bonus : 
	@echo "${MAGENTA}====================================="
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(BONUS) -o $(BONUS_NAME)
	@echo "\n====== $(BONUS_NAME) compiling finished ======\n"


clean :
	@echo "$(MAGENTA)====================================="
	@echo "====== object files removed ======\n"

fclean : clean
	@echo "${YELLOW}====================================="
	rm -f $(NAME)
	rm -rf $(NAME).dSYM
	@echo "\n====== binary files removed =======\n"

re : fclean all

.PHONY : all clean fclean re
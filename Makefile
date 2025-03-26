NAME = cub3D

#CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

MLXFLAGS = -L/usr/X11/lib -lX11 -lXext -lm #-O3

SRCS_DIR = ./srcs/

# should be used in the final version
#SRCS := $(wildcard $(SRCS_DIR)/**/*.c) $(wildcard $(SRCS_DIR)/*.c)

SRCS := $(shell find $(SRCS_DIR) -type f -name "*.c" ! -name "parser_test.c")

LIB_DIR = ./lib

LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLXLIB_DIR = $(LIB_DIR)/minilibx
MLXLIB = $(MLXLIB_DIR)/libmlx.a

OBJS := $(patsubst %.c, %.o, $(SRCS))

HEADERS = cub.h

.PHONY: clean fclean re all valgrind

all: $(NAME)

$(NAME): $(OBJS) $(MLXLIB) $(LIBFT)
	cc $(CFLAGS) $(OBJS) $(MLXLIB) $(LIBFT) $(MLXFLAGS) -o $@

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

$(MLXLIB):
	$(MAKE) -C $(MLXLIB_DIR)

$(SRCS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS)
	cc $(CFLAGS) -I. -c $< -o $@

install_on_linux:
	@sudo apt update && sudo apt install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev libbsd-dev

bonus: all

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLXLIB_DIR)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

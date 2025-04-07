NAME = parser_test

#CFLAGS = -Wall -Wextra -Werror -g # -fsanitize=address
CFLAGS = -g
# Directories
SRCS_DIR = ../parser
LIB_DIR = ../../lib

LIBFT_DIR = $(LIB_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Find all .c files in the parser directory and its subdirectories
SRCS := $(shell find $(SRCS_DIR) -type f -name "*.c")

# Convert .c files to .o files
OBJS := $(SRCS:.c=.o)

.PHONY: clean fclean re all valgrind run_test

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	cc $(CFLAGS) $(OBJS) $(LIBFT) -o $@

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

# Rule to compile .c files into .o files
%.o: %.c
	cc $(CFLAGS) -I. -c $< -o $@

bonus: all

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

# New rule: Compile and run parser_test with valgrind
run_test: $(NAME)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME) test_maps/test_map.cub

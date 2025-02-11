
#ifndef PARSER_H
#define PARSER_H

# include "../lib/libft/libft.h"
# include "../lib/libft/gnl/get_next_line_bonus.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_map
{
	int	row;
	int	column;
	int	s_count;
	char	cardinal_direction;
	int	cardinal_direction_count;
} t_map;
#endif //PARSER_H

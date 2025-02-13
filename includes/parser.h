
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
	char	**matrix;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;	// Player’s starting direction ('N', 'S', 'E', 'W')
} t_map;

#endif //PARSER_H

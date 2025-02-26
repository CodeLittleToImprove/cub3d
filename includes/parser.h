
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
	char		**grid;
	size_t		max_width;
	size_t		max_height;
	size_t		player_x;
	size_t		player_y;
	char		player_dir;	// Player’s starting direction ('N', 'S', 'E', 'W')
} t_map;

//parser_utils.c
void	print_grid(char **grid);
void	free_grid(char **grid);
void	print_grid_character(char **grid);
bool	is_empty_line(char *line);
size_t	count_leading_white_space(char *line);
char	*skip_empty_lines(int fd, size_t *empty_lines);
char	*trim_space_and_copy(char *line, size_t width);

//parser_test.c
size_t	count_width(char *file_name, size_t row, t_map *map);

//parser_map_validation.c
bool	is_map_valid(t_map *map);
bool	flood_fill(t_map *map, size_t y, size_t x);

//parser_map_utils.c
bool	valid_map_borders(t_map *map);
void	detect_player_pos(t_map *map);
#endif //PARSER_H

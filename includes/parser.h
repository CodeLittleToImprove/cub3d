
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

#define BUFFER_SIZE 1024
#define MAX_LINE 256

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
bool	detect_map_start(const char *line, bool *has_map_started, bool *is_valid_start);
//bool	is_map_valid(t_map *map);
bool	reached_boundary(t_map *map, size_t y, size_t x);
bool	has_valid_characters_only(char *file_name);
bool	is_valid_map_line(const char *line);
bool	is_valid_start_or_end_line(const char *line);
bool	write_and_track_last_line(int fd_out, const char *line, char **last_map_line);

//parser_map_utils.c
bool	valid_map_borders(t_map *map);
void	detect_player_pos(t_map *map);

//fd_utils.c
int	open_input_file(const char *filename);
int	open_output_file(const char *outputfilename);

//buffer_utils.
// void	allocate_buffers(char **buffer, char **line, char **last_map_line);
// void	free_buffers(char *buffer, char *line, char *last_map_line);
#endif //PARSER_H

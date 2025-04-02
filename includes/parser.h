
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
	char		player_dir;	// Player’s starting direction ('N', 'S', 'E', 'W')
	size_t		max_width;
	size_t		max_height;
	size_t		player_x;
	size_t		player_y;
	size_t		map_end_line;
} t_map;

typedef struct s_map_state
{
	bool	has_map_started;
	bool	is_valid_start;
	bool	is_valid_end;
	char	*last_map_line;
} t_map_state;

typedef struct s_colors
{
	int		rgb_floor[3];
	int		rgb_ceiling[3];
	size_t	color_start_line;
	bool	has_floor; // not properly used right now
	bool	has_ceiling; // not properly used right now
} t_colors;

typedef struct s_textures
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	bool	no_set;
	bool	so_set;
	bool	we_set;
	bool	ea_set;
	size_t	last_texture_line;
} t_textures;

//parser_color_utils;
void	set_default_values_color(t_colors *colors);
bool	is_valid_rgb(char *str);
char	*ft_strtok_r(char *str, char *delim, char **saveptr);
size_t	skip_leading_chars(char *str, size_t i, char *skip_chars);
bool	is_invalid_color_line(char *line);

//parser_color.c
bool	detect_color(const char *filename, t_colors *colors);
bool	parse_color(char *line, t_colors *colors, char type);
bool	check_and_parse_color(char *line, t_colors *colors, char type, bool *found_flag);

//parser_textures_utils.c
void	set_default_values_textures(t_textures *textures);
char	*extract_texture_path(char *line, char *key);
bool	is_valid_texture_path(char *path);
bool	is_invalid_texture_line(char *line);

//parser_textures.c
bool	detect_textures(char *filename, t_textures *textures);

//parser_extract_map_utils.c
void	set_default_values_map(t_map *map);
bool	write_and_track_last_line(int fd_out, const char *line, char **last_map_line);
bool	is_valid_start_or_end_line(const char *line);
bool	has_valid_characters_only(char *file_name);

//parser_map_extract.c
bool	extract_map(const char *filename, t_map *map);

//parser_utils.c
bool	is_empty_line(char *line);
size_t	count_leading_white_space(char *line);
char	*skip_empty_lines(int fd, size_t *empty_lines);
char	*trim_space_and_copy(char *line, size_t width);

//parser_map_validation.c
bool	detect_map_start(char *line, t_map_state *state);
bool	reached_boundary(t_map *map, size_t y, size_t x);
bool	is_valid_map_line(const char *line);
void	detect_player_pos(t_map *map);

//parser_read_map.c;
void	read_map_file(char *file_name, t_map *map);

//fd_utils.c
int		open_input_file(const char *filename);
int		open_output_file(const char *outputfilename);
bool	handle_invalid_color_line(char *line, size_t line_number, int fd, bool first_color_found);

//print_utils.c
void	print_colors(const t_colors *colors);
void	print_grid(char **grid);
void	print_grid_character(char **grid);
void	print_textures(t_textures *textures);

//parser_free_utils.c
void	free_grid(char **grid);
void	free_textures(t_textures *textures);
#endif //PARSER_H

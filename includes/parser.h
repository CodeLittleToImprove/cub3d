
#ifndef PARSER_H
# define PARSER_H

# define MAX_MAP_HEIGHT 10000
# define MAX_MAP_WIDTH 10000

# include "../lib/libft/libft.h"
# include "../lib/libft/gnl/get_next_line_bonus.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct s_map
{
	char		**grid;
	char		player_dir;	// Player’s starting direction ('N', 'S', 'E', 'W')
	size_t		max_width;
	size_t		max_height;
	size_t		player_x;
	size_t		player_y;
	size_t		map_end_line;
}	t_map;

typedef struct s_grid_state
{
	size_t	width;
	size_t	row;
	size_t	empty_lines;
}	t_grid_state;

typedef struct s_map_state
{
	bool	has_map_started;
	bool	is_valid_start;
	bool	is_valid_end;
	char	*last_map_line;
}	t_map_state;

typedef struct s_colors
{
	int		rgb_floor[3];
	int		rgb_ceiling[3];
	int		rgb_hex_floor;
	int		rgb_hex_ceiling;
	size_t	color_start_line;
	bool	has_floor;
	bool	has_ceiling;
	bool	first_color_found;
	bool	found_both_colors;
}	t_colors;

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
	bool	all_set;
	size_t	last_texture_line;
}	t_textures;

//fd_utils.c
int		open_input_file(const char *filename);
int		open_output_file(const char *outputfilename);
int		rgb_to_hex(int rgb[3]);
void	set_rgb_hex_in_colors(t_colors *colors);

//parser_color.c
bool	detect_color(const char *filename, t_colors *colors);
bool	parse_color(char *line, t_colors *colors, char type);
bool	check_and_parse_color(char *line, t_colors *colors,
			char type, bool *found_flag);

//parser_color_utils;
bool	is_valid_rgb(char *str);
char	*ft_strtok_r(char *str, char *delim, char **saveptr);
size_t	skip_leading_chars(char *str, size_t i, char *skip_chars);
bool	is_invalid_color_line(char *line);
bool	validate_color_line(char *line, size_t line_number,
			int fd, t_colors *colors);

//parser_extract_map.c
bool	extract_map(const char *filename, t_map *map);

//parser_extract_map_utils.c
bool	write_and_track_last_line(int fd_out, char *line,
			t_map_state *state);
bool	is_valid_start_or_end_line(const char *line);

//parser_free_utils.c
int		handle_error(const char *message, t_map *map,
			t_textures *textures, int code);
void	free_grid(char **grid);
bool	handle_texture_error_and_clean(char *line, int fd);
void	free_textures(t_textures *textures);
void	parser_cleanup(t_map *map, t_textures *textures);

//parser_init.c
void	set_default_values_color(t_colors *colors);
void	set_default_values_map(t_map *map);
void	set_default_values_textures(t_textures *textures);
void	set_parser_default_values(t_map *map, t_textures *textures);

//parser_map_validation.c
bool	detect_map_start(char *line, t_map_state *state);
char	**copy_grid(char **grid, size_t height);
bool	reached_boundary(t_map *map, char **copy_grid, size_t y, size_t x);
bool	is_valid_map_line(const char *line);
void	detect_player_pos(t_map *map);

//parser_map_validation_utils.c
bool	has_valid_characters_only(char *file_name);

//parser_read_map.c;
bool	read_map_file(char *file_name, t_map *map);

//parser_read_map_utils.c;
size_t	count_width(char *file_name, size_t row);
size_t	count_height_and_free(char *file_name);
bool	init_map_height(char *file_name, t_map *map);
//parser_textures.c
bool	detect_textures(char *filename, t_textures *textures);

//parser_textures_utils.c
char	*extract_texture_path(char *line, char *key);
bool	is_valid_texture_path(char *path);
bool	is_texture_identifier(char *line);
bool	is_duplicate_texture_line(char *line, size_t line_number,
			t_textures *textures, int fd);
bool	is_invalid_texture_line(char *line);

//parser_utils.c
bool	is_empty_line(char *line);
size_t	count_leading_white_space(char *line);
char	*skip_empty_lines(int fd, size_t *empty_lines);
char	*trim_space_and_copy(char *line, size_t width);
bool	is_cub_file(const char *filename);

//print_utils.c
void	print_colors(const t_colors *colors);
void	print_grid(char **grid);
void	print_grid_character(char **grid);
void	print_textures(t_textures *textures);

#endif //PARSER_H

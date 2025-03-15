#include "../includes/parser.h"

size_t	count_height_and_free(char *file_name)
{
	int			fd;
	char		*line;
	size_t		height;

	fd = open(file_name, O_RDONLY, 0);
//	if (fd <= 0)
//	//		ft_error_and_exit("file does not exist or no permission");
	line = get_next_line(fd);
	height = 0;
	if (line == NULL)
		return (0);
	while (line != NULL)
	{
		if (is_empty_line(line))
		{
			free(line);
			close(fd);
			return (0);
		}
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

size_t	count_width(char *file_name, size_t row, t_map *map)
{
	int		fd;
	size_t	current_line;
	size_t	width;
	char	c;
	bool	found_first_char;

	fd = open(file_name, O_RDONLY, 0);
	if (fd <= 0)
		return (perror("file does not exist or no permission"), 0);
	current_line = 0;
	width = 0;
	found_first_char = false;
	while (read(fd, &c, 1) == 1)
	{
		if (c == '\n' && current_line++ == row)
			break;
		if (current_line == row)
		{
			if (!found_first_char && ft_isspace(c))
				continue;
			found_first_char = true;
			width++;
		}
	}
	if (width > map->max_width)
		map->max_width = width;
	close(fd);
	return (width);
}

char	**create_grid(char *file_name, t_map *map)
{
	char	**grid;
	int		fd;
	char	*line;
	size_t	width;
	size_t	row;
	size_t	empty_lines;

	map->max_height = count_height_and_free(file_name);
	if(map->max_height == 0)
		return (NULL);
	printf("height : %ld\n\n", map->max_height);
	grid = malloc((map->max_height + 1) * sizeof(char *));
	if (!grid)
	{
		perror("Memory allocation failed");
		return (NULL);
	}
	fd = open(file_name, O_RDONLY, 0);
	row = 0;
	empty_lines = 0;
	while (row < map->max_height)
	{
		line = skip_empty_lines(fd, &empty_lines);
		if (!line)
			break;
		printf("row[%ld] current processed line: %s\n", row, line);
		width = count_width(file_name, row + empty_lines, map);
		printf("width : %ld\n\n", width);
		grid[row] = trim_space_and_copy(line, width);
		free(line);
		row++;
	}
	close(fd);
	grid[row] = NULL;
	return (grid);
}

void	set_default_values_map(t_map *map)
{
	map->max_height = 0;
	map->max_width = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = '\0';
	map->map_end_line = 0;
}

void	read_map_file(char *file_name, t_map *map)
{

	if (has_valid_characters_only(file_name) == false)
	{
		printf("terminate program because of invalid characters \n");
		exit (-1);
	}
//	set_default_values_map(map);
	map->grid = create_grid(file_name, map);
	if(map->grid == NULL)
	{
		printf("Map is invalid after counting height \n");
		exit (-1);
	}
//	printf("map maxwidth %d\n", map->max_width);
//	printf("map maxheight %d\n", map->max_height);
//	printf("map width :%d for height[%d]\n", strlen(map->grid[1]), 1);
	detect_player_pos(map);
	// printf("array value at player value %c \n", map->grid[map->player_y][map->player_x]);
	printf("player pos value y:%ld x:%ld\n", map->player_y, map->player_x );
	print_grid(map->grid);
	if (reached_boundary(map, map->player_y, map->player_x) == true)
	{
		printf("Map is open therefore invalid \n");
	}
	printf("\nafter flood fill\n");
	print_grid(map->grid);
//	print_grid_character(map->grid);
}

int	process_map(int fd_in, int fd_out, t_map *map)
{
	char	*line;
	char	*last_map_line;
	bool	has_map_started;
	bool	is_valid_start;
	bool	is_valid_end;

	line = get_next_line(fd_in);
	if (line == NULL)
		exit(-1);
	has_map_started = false;
	is_valid_start = false;
	is_valid_end = false;
	set_default_values_map(map);
	printf("before increase map end line %ld\n", map->map_end_line);
	while (line != NULL)
	{
		if (!detect_map_start(line, &has_map_started, &is_valid_start))
		{
			return(free(line), -1);
		}
		if (has_map_started && is_valid_start)
		{
			if (!write_and_track_last_line(fd_out, line, &last_map_line))
			{
				return(free(line), -1);
			}
		}
		free(line);
		line = get_next_line(fd_in);
		map->map_end_line++;
	}
	if (last_map_line && is_valid_start_or_end_line(last_map_line))
		is_valid_end = true;
	if (has_map_started && is_valid_start && is_valid_end)
	{
		printf("after increase map end line %ld\n", map->map_end_line); // it's + 1 after the last line
		printf("map contains properly start and ending\n");
		return (0);
	}
	return (-1);
}

bool	extract_map(const char *filename, t_map *map)
{
	int		fd_in;
	int		fd_out;

	fd_in = open_input_file(filename);
	fd_out = open_output_file("temp_map.cub");

	if (process_map(fd_in, fd_out, map) == -1)
		{
			printf("debug: map invalid before copying");
		//delete temp map cub later
			return (false);
		}
	close(fd_in);
	close(fd_out);
	return (true);
}

void	set_default_values_color(t_colors *colors)
{
	colors->rgb_floor[0] = 0;
	colors->rgb_floor[1] = 0;
	colors->rgb_floor[2] = 0;
	colors->rgb_ceiling[0] = 0;
	colors->rgb_ceiling[1] = 0;
	colors->rgb_ceiling[2] = 0;
	colors->has_floor = false; // probably not needed
	colors->has_ceiling = false; // probably not needed
	colors->color_start_line = 0;
}

bool	detect_color(const char *filename, t_colors *colors)
{
	int		fd;
	char	*line;
	bool	found_floor;
	bool	found_ceiling;
	bool	first_color_found;
	size_t	line_number;

	fd = open_input_file(filename);
	if (fd < 0)
		return (false);
	line = get_next_line(fd);
	// printf("line in detect color:%s\n", line);
	set_default_values_color(colors);
	found_floor = false;
	found_ceiling = false;
	first_color_found = false;
	line_number = 0;
	while (line!= NULL)
	{
		if (check_and_parse_color(line, colors, 'F', &found_floor) ||
				check_and_parse_color(line, colors, 'C', &found_ceiling))
		{
			if (!first_color_found)
			{
				colors->color_start_line = line_number;
				first_color_found = true;
			}
		}
		free(line);
		if (found_floor && found_ceiling)
			return (true);
		line = get_next_line(fd);
		line_number++;
	}
	close(fd);
	return (false);
}

bool	is_invalid_texture_line(char *line)
{
	if (is_empty_line(line))
		return (false);
	if (!(ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0 ||
		ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0))
		return (true);
	return (false);
}

bool	is_valid_texture_path(char *path)
{
	int	fd;

//	printf("path in is valid texture path:%s\n", path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening texture file");
		return (false);
	}
	close(fd);
	return (true);
}

char	*extract_texture_path(char *line, char *key)
{
	char	*raw_path;
	char	*trimmed_path;

	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, key, ft_strlen(key)) != 0)
		return (NULL);
	line += ft_strlen(key);
	while (*line == ' ' || *line == '\t')
		line++;
	raw_path = ft_strdup(line);
	if (!raw_path)
	{
		printf("Error: Memory allocation failed\n");
		return (NULL);
	}
	// printf("raw_path %s\n", raw_path);
	trimmed_path = ft_strtrim(raw_path, " \n");
	// printf("trimmed_path %s\n", trimmed_path);
	free(raw_path);
	return (trimmed_path);
}

bool	assign_texture_path(char *line, char *key, char **texture_path, bool *valid_texture)
{
	if (*valid_texture)
	{
		// printf("Error: Duplicate texture assignment for %s\n", key);
		return (false);
	}
	*texture_path = extract_texture_path(line, key);
	if (!*texture_path)
	{
		// printf("Error: Failed to extract texture path for %s\n", key);
		return (false);
	}
	// printf("Extracted texture path for %s: %s\n", key, *texture_path);
	if (**texture_path == '\0')
	{
		printf("Error: Extracted texture path for %s is empty.\n", key);
		free(*texture_path);
		*texture_path = NULL;
		return (false);
	}
	if (!is_valid_texture_path(*texture_path))
	{
		printf("Error: Texture file for %s is invalid or does not exist: %s\n", key, *texture_path);
		free(*texture_path);
		*texture_path = NULL;
		return (false);
	}

	*valid_texture = true;
	// printf("Successfully assigned texture: %s -> %s\n", key, *texture_path);
	return (true);
}

bool	process_texture_line(char *line, size_t line_number, t_textures *textures)
{
	if (assign_texture_path(line, "NO", &textures->no_texture, &textures->no_set) ||
		assign_texture_path(line, "SO", &textures->so_texture, &textures->so_set) ||
		assign_texture_path(line, "WE", &textures->we_texture, &textures->we_set) ||
		assign_texture_path(line, "EA", &textures->ea_texture, &textures->ea_set))
	{
		printf("DEBUG texture detected on line %ld: %s\n", line_number, line);
		return (true);
	}
	return (false);
}

void	set_default_values_textures(t_textures *textures)
{
	textures->no_texture = NULL;
	textures->so_texture = NULL;
	textures->we_texture = NULL;
	textures->ea_texture = NULL;
	textures->no_set = false;
	textures->so_set = false;
	textures->we_set = false;
	textures->ea_set = false;
	textures->last_texture_line = 0;
}

bool	detect_textures(char *filename, t_textures *textures)
{
	int		fd;
	char	*line;
	size_t	line_number;
	fd = open_input_file(filename);
	set_default_values_textures(textures);
	line = get_next_line(fd);
	line_number = 0;
	while (line != NULL)
	{
		if (is_invalid_texture_line(line) &&
			(textures->no_set || textures->so_set || textures->we_set || textures->ea_set))
		{
			printf("Error: Found non-texture line within texture definitions at line %ld: %s\n", line_number, line);
			free(line);
			close(fd);
			return (false);
		}
		process_texture_line(line, line_number, textures);
		printf("DEBUG: no_set=%d, so_set=%d, we_set=%d, ea_set=%d\n",
		textures->no_set, textures->so_set, textures->we_set, textures->ea_set);
		free(line);
		if (textures->no_set && textures->so_set && textures->we_set && textures->ea_set)
		{
			textures->last_texture_line = line_number;
			break;
		}
		line = get_next_line(fd);
		line_number++;
	}
	close(fd);
	printf("FINAL DEBUG: no_set=%d, so_set=%d, we_set=%d, ea_set=%d\n",
	   textures->no_set, textures->so_set, textures->we_set, textures->ea_set);
	return (textures->no_set && textures->so_set && textures->we_set && textures->ea_set);
}

int	main(int argc, char *argv[])
{
	t_map		map;
	t_colors	colors;
	t_textures	textures;

	if (argc != 2)
		return (-1);

	// if(detect_color(argv[1], &colors))
	// {
	// 	printf("colors extraction success\n");
	// 	print_colors(&colors);
	// }
	// else
	// 	printf("colors extraction fail \n"); // stop program
	//  if (extract_map(argv[1], &map))
	//  {
	//  	printf("map extraction success\n");
	//  }
	// else
	// {
	// 	printf("map extraction fail \n");
	// }
//	printf("map->end_line %ld\n", map.map_end_line);
	if (detect_textures(argv[1], &textures))
	{
		printf("Textures extracted successfully:\n");
		printf("NO: %s\n", textures.no_texture);
		printf("SO: %s\n", textures.so_texture);
		printf("WE: %s\n", textures.we_texture);
		printf("EA: %s\n", textures.ea_texture);
		printf("Last texture line: %ld\n", textures.last_texture_line);
	}
	else
	{
		printf("Failed to extract all textures.\n");
	}
	// read_map_file(argv[1], &map); // reads the original file
	// read_map_file("temp_map.cub", &map); // reads the temp file for testing
}
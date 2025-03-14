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

bool	is_invalid_color_line(char *line)
{
	if (is_empty_line(line))
		return (false);

	// Allow only valid color keys (F or C)
	if (!(ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0))
		return (true);

	return (false);
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
		if (first_color_found && is_invalid_color_line(line))
		{
			printf("Error: Found non-color line within color definitions at line %ld: %s\n", line_number, line);
			free(line);
			close(fd);
			return (false);
		}
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

int	main(int argc, char *argv[])
{
	t_map		map;
	t_colors	colors;
	t_textures	textures;

	if (argc != 2)
		return (-1);

	if(detect_color(argv[1], &colors))
	{
		printf("colors extraction success\n");
		print_colors(&colors);
	}
	else
		printf("colors extraction fail \n"); // stop program
	//  if (extract_map(argv[1], &map))
	//  {
	//  	printf("map extraction success\n");
	//  }
	// else
	// {
	// 	printf("map extraction fail \n");
	// }
//	printf("map->end_line %ld\n", map.map_end_line);
	// if (detect_textures(argv[1], &textures))
	// {
	// 	printf("Textures extracted successfully:\n");
	// 	print_textures(&textures);
	// }
	// else
	// {
	// 	printf("Failed to extract all textures.\n");
	// }
	// read_map_file(argv[1], &map); // reads the original file
	// read_map_file("temp_map.cub", &map); // reads the temp file for testing
}
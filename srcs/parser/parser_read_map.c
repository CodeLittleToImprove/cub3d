#include "../../includes/parser.h"

static void	init_width_vars(size_t *current_line, size_t *width,
		bool *found_first_char)
{
	*current_line = 0;
	*width = 0;
	*found_first_char = false;
}

size_t	count_width(char *file_name, size_t row, t_map *map)
{
	int		fd;
	size_t	current_line;
	size_t	width;
	char	c;
	bool	found_first_char;

	fd = open_input_file(file_name);
	if (fd <= 0)
		return (0);
	init_width_vars(&current_line, &width, &found_first_char);
	while (read(fd, &c, 1) == 1)
	{
		if (c == '\n' && current_line++ == row)
			break ;
		if (current_line == row)
		{
			if (!found_first_char && ft_isspace(c))
				continue ;
			found_first_char = true;
			width++;
		}
	}
	if (width > map->max_width)
		map->max_width = width;
	return (close(fd), width);
}

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

static bool	init_map_height(char *file_name, t_map *map)
{
	map->max_height = count_height_and_free(file_name);
	return (map->max_height > 0);
}

char	**create_grid(char *file_name, t_map *map)
{
	char			**grid;
	int				fd;
	char			*line;
	t_grid_state	state;

	if (!init_map_height(file_name, map))
		return (NULL);
	// printf("height : %ld\n\n", map->max_height);
	grid = malloc((map->max_height + 1) * sizeof(char *));
	if (!grid)
		return (perror("Memory allocation failed"), NULL);
	fd = open_input_file(file_name);
	state.row = 0;
	state.empty_lines = 0;
	while (state.row < map->max_height)
	{
		line = skip_empty_lines(fd, &state.empty_lines);
		if (!line)
			break ;
		// printf("row[%ld] current processed line: %s\n", row, line);
		state.width = count_width(file_name, state.row + state.empty_lines, map);
		// printf("width : %ld\n\n", width);
		grid[state.row] = trim_space_and_copy(line, state.width);
		free(line);
		state.row++;
	}
	grid[state.row] = NULL;
	return (close(fd), grid);
}

bool	read_map_file(char *file_name, t_map *map)
{
	char	**map_copy;

	if (has_valid_characters_only(file_name) == false)
		return (printf(" detected invalid characters stop the program \n"), false);
	map->grid = create_grid(file_name, map);
	if(map->grid == NULL)
		return (printf("Map grip is NULL \n"), false);
//	printf("map maxwidth %d\n", map->max_width);
//	printf("map maxheight %d\n", map->max_height);
//	printf("map width :%d for height[%d]\n", strlen(map->grid[1]), 1);
	detect_player_pos(map);
	// printf("array value at player value %c \n", map->grid[map->player_y][map->player_x]);
	// printf("player pos value y:%ld x:%ld\n", map->player_y, map->player_x );
	map_copy = copy_grid(map->grid, map->max_height);
	if (!map_copy)
		return (printf("Failed to allocate memory for map copy\n"), false);
	if (reached_boundary(map, map_copy, map->player_y, map->player_x) == true)
	{
		free_grid(map_copy);
		return (printf("Map is open therefore invalid \n"), false);
	}
	free_grid(map_copy);
//	 printf("\nafter flood fill\n");
	// print_grid(map->grid);
//	print_grid_character(map->grid);
	return (true);
}

#include "../../includes/parser.h"

void	init_grid_state(t_grid_state	*state)
{
	state->width = 0;
	state->row = 0;
	state->empty_lines = 0;
}

char	**create_grid(char *file, t_map *map)
{
	char			**grid;
	int				fd;
	char			*line;
	t_grid_state	state;

	if (!init_map_height(file, map))
		return (NULL);
	// printf("height : %ld\n\n", map->max_height);
	grid = malloc((map->max_height + 1) * sizeof(char *));
	if (!grid)
		return (perror("Memory allocation failed"), NULL);
	fd = open_input_file(file);
	init_grid_state(&state);
	while (state.row < map->max_height)
	{
		line = skip_empty_lines(fd, &state.empty_lines);
		if (!line)
			break ;
		// printf("row[%ld] current processed line: %s\n", row, line);
		state.width = count_width(file, state.row + state.empty_lines, map);
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
		return (printf("detected invalid characters\n"), false);
	map->grid = create_grid(file_name, map);
	if (map->grid == NULL)
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

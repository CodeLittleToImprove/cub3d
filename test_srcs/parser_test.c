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
}

void	read_map_file(char *file_name, t_map *map)
{

	if (has_valid_characters_only(file_name) == false)
	{
		printf("terminate program because of invalid characters \n");
		exit (-1);
	}
	set_default_values_map(map);
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

int	process_map(int fd_in, int fd_out)
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
	while (line != NULL)
	{
		if (!detect_map_start(line, &has_map_started, &is_valid_start))
		{
			free(line);
			return (-1);
		}
		if (has_map_started && is_valid_start)
		{
			if (!write_and_track_last_line(fd_out, line, &last_map_line))
			{
				free(line);
				return (-1);
			}
		}
		free(line);
		line = get_next_line(fd_in);
	}
	if (last_map_line && is_valid_start_or_end_line(last_map_line))
		is_valid_end = true;
	if (has_map_started && is_valid_start && is_valid_end)
	{
		printf("map contains properly start and ending\n");
		return (0);
	}
	return (-1);
}

void	extract_map(const char *filename)
{
	int		fd_in;
	int		fd_out;

	fd_in = open_input_file(filename);
	fd_out = open_output_file("temp_map.cub");

	if (process_map(fd_in, fd_out) == -1)
		{
			printf("debug: map invalid before copying");
		//delete temp map cub
			exit (-1);
		}
	close(fd_in);
	close(fd_out);
}

int	main(int argc, char *argv[])
{
	t_map	map;

	if (argc != 2)
		return (-1);
	extract_map(argv[1]);
	// read_map_file(argv[1], &map); // reads the original file
	read_map_file("temp_map.cub", &map); // reads the temp file for testing
}
#include "../includes/parser.h"

bool is_valid_map_line(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (false);
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

bool is_valid_start_or_end_line(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (false);
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

void	validate_last_line(const char *last_map_line)
{
	int	fd;

	if (!is_valid_map_line(last_map_line))
	{
		write(STDERR_FILENO, "Error: Last map line is not enclosed by walls!\n", 47);
		// "Delete" the file by truncating it
		fd = open("temp_map.cub", O_WRONLY | O_TRUNC);
		if (fd >= 0)
			close(fd);
		exit(EXIT_FAILURE);
	}
}

bool	reached_boundary(t_map *map, size_t y, size_t x)
{
	if (y >= map->max_height)
		return (true);
	if (x >= ft_strlen(map->grid[y]))
		return (true);
	if (map->grid[y][x] == '1' || map->grid[y][x] == 'V')
	{
		if (map->grid[y][x] == '1' )
			printf("Encountered a wall at (y = %ld, x = %ld)\n", y, x);
		if (map->grid[y][x] == 'V' )
			printf("Already visited (y = %ld, x = %ld)\n", y, x);
		return (false);
	}
	map->grid[y][x] = 'V';

	if (reached_boundary(map, y + 1, x)) // Down
	{
		printf("flood_filled moved down \n");
		return (true);
	}
	if (reached_boundary(map, y - 1, x)) // Up
	{
		printf("flood_filled moved up \n");
		return (true);
	}
	if (reached_boundary(map, y, x + 1)) // Right
	{
		printf("flood_filled moved right \n");
		return (true);
	}
	if (reached_boundary(map, y, x - 1))
	{
		printf("flood_filled moved left \n");
		return (true);
	}
	return (false);
}

bool	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

bool	has_valid_characters_only(char *file_name)
{
	int		fd;
	bool	file_is_valid;
	char	c;
	size_t	player_count;

	fd = open(file_name, O_RDONLY, 0);
	file_is_valid = true;
	player_count = 0;
	if (fd <= 0)
		return(perror("file does not exist or no permission"),false);
	while (read(fd, &c, 1) == 1)
	{
		if (c == '\n')
			continue;
		if (!is_valid_char(c))
		{
			file_is_valid = false;
			printf("Invalid character found: '%c'\n", c); // remove in final parser
			break;
		}
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			player_count++;
		if (player_count > 1)
		{
			file_is_valid = false;
			printf("Error: Multiple player start positions found.\n");
			break;
		}
	}
	if (player_count == 0)
		{
			file_is_valid = false;
			printf("Error: No player start position found.\n");
		}
	close(fd);
	return (file_is_valid);
}

bool	detect_map_start(const char *line, bool *has_map_started, bool *is_valid_start)
{
	if (!*has_map_started && is_valid_map_line(line))
	{
		printf("DEBUG: First map line detected: %s\n", line);
		*has_map_started = true;
		*is_valid_start = is_valid_start_or_end_line(line);
	}

	// Detect an empty line after the map starts (invalid case)
	if (*has_map_started && is_empty_line(line))
	{
		printf("Detected empty line after map start.\n");
		return (false);
	}

	return (true);
}

bool	write_and_track_last_line(int fd_out, const char *line, char **last_map_line)
{
	write(fd_out, line, ft_strlen(line));

	// If the line doesn't end with a newline, it's the last map line
	if (line[ft_strlen(line) - 1] != '\n')
	{
		*last_map_line = malloc(ft_strlen(line) + 1);
		if (!*last_map_line)
			return (false);
		ft_strlcpy(*last_map_line, line, ft_strlen(line) + 1);
		printf("DEBUG: This should be the last line: %s\n", *last_map_line);
	}
	return (true);
}
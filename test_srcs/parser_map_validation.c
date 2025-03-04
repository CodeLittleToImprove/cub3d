#include "../includes/parser.h"

//bool	is_map_valid(t_map *map)
//{
//	if (valid_map_borders(map) == true)
//	{
//		printf("border are valid \n");
//		return (true);
//	}
//
//	return (false);
//}

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

bool is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

bool	has_valid_characters_only(char *file_name)
{
	int		fd;
	bool	file_is_valid;
	char	c;

	fd = open(file_name, O_RDONLY, 0);
	file_is_valid = true;
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
	}
	close(fd);
	return (file_is_valid);
}
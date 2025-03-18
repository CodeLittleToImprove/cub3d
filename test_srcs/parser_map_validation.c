#include "../includes/parser.h"

bool	is_valid_map_line(const char *line)
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

void	detect_player_pos(t_map *map)
{
	size_t	column;
	size_t	max_height;
	size_t	row;

	column = 0;
	max_height = map->max_height;
	while (column < max_height)
	{
		row = 0;
		while (map->grid[column][row]!= '\0')
		{
			if (map->grid[column][row] == 'N' ||
			map->grid[column][row] == 'S' ||
			map->grid[column][row] == 'E' ||
			map->grid[column][row] == 'W')
			{
				map->player_x = row;
				map->player_y = column;
				map->player_dir = map->grid[column][row];
				// printf("Player pos detected at x=%ld, y=%ld\n", map->player_x, map->player_y);
				printf("Player dir %c\n", map->player_dir);
				return ;
			}
			row++;
		}
		column++;
	}
}
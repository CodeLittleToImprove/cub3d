#include "../includes/parser.h"

bool	is_map_valid(t_map *map)
{
	if (valid_map_borders(map) == true)
	{
		printf("border are valid \n");
		return (true);
	}

	return (false);
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
		return true;
	}
	if (reached_boundary(map, y - 1, x)) // Up
	{
		printf("flood_filled moved up \n");
		return true;
	}
	if (reached_boundary(map, y, x + 1)) // Right
	{
		printf("flood_filled moved right \n");
		return true;
	}
	if (reached_boundary(map, y, x - 1))
	{
		printf("flood_filled moved left \n");
		return true; // Left
	}
	return (false);
}

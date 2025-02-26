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

bool	flood_fill(t_map *map, size_t y, size_t x)
{
	if (y >= map->max_height)
		return (true);
	if (x >= ft_strlen(map->grid[y]))
		return (true);
	if (map->grid[y][x] == '1' || map->grid[y][x] == 'V')
		return (false);
	map->grid[y][x] = 'V';

	if (flood_fill(map, y + 1, x)) // Down
	{
		printf("flood_filled down failed \n");
		return true;
	}
	if (flood_fill(map, y - 1, x)) // Up
	{
		printf("flood_filled up failed \n");
		return true;
	}
	if (flood_fill(map, y, x + 1)) // Right
	{
		printf("failed pos[%ld][%ld]", y, x + 1);
		printf("flood_filled right failed \n");
		return true;
	}
	if (flood_fill(map, y, x - 1))
	{
		printf("flood_filled left failed \n");
		return true; // Left
	}


	return (false);
}

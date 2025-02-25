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

void	flood_fill(t_map *map, size_t y, size_t x)
{
	if (y < 0 || y >= map->max_height)
		return ;

	if (x < 0 || x >= (size_t)ft_strlen(map->grid[y]))
		return ;
	if (map->grid[y][x] == '1' || map->grid[y][x] == 'V')
		return ;
	map->grid[y][x] = 'V';

	flood_fill(map, y + 1, x); //Down
	flood_fill(map, y - 1, x); //Up
	flood_fill(map, y, x + 1); //Right
	flood_fill(map, y, x - 1); //Left
}

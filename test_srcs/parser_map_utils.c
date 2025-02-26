#include "../includes/parser.h"

//bool	line_contain_only_ones(const char *line)
//{
//	size_t	index;
//
//	index = 0;
//	while (line[index] != '\0')
//	{
//		if (line[index] != '1')
//			return (false);
//		index++;
//	}
//	return (true);
//}

bool	valid_map_borders(t_map *map)
{
	size_t	max_height;
	size_t	x;
	size_t	y;

	max_height = map->max_height - 1;
	x = 0;
	// Check top row (map->grid[0])
	while (x < ft_strlen(map->grid[0]))
	{
		if (map->grid[0][x++] != '1')
		{
			printf("Top border not valid \n");
			return (false);
		}
	}
	// Check bottom row (map->grid[max_height - 1])
	x = 0;
	while (x < ft_strlen(map->grid[max_height]))
	{
		if (map->grid[max_height][x++] != '1')
		{
			printf("Bottom border not valid \n");
			return (false);
		}
	}
	// Check leftmost column for each row
	y = 0;
	while (y <= max_height)
	{
		if (map->grid[y++][0] != '1')
		{
			printf("Left border not valid \n");
			return (false);
		}
	}
	y = 0;
	// Check rightmost column for each row
	while (y <= max_height)
	{
		if (map->grid[y++][map->max_width - 1] != '1')
		{
			printf("Right border not valid \n");
			return (false);
		}
	}
	return (true);
}
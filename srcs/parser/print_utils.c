#include "../../includes/parser.h"

void	print_colors(const t_colors *colors)
{
	printf("Floor RGB: [%d, %d, %d]\n",
		colors->rgb_floor[0], colors->rgb_floor[1], colors->rgb_floor[2]);
	// Print Hex value for floor
	printf("Floor Hex: 0x%X\n", colors->rgb_hex_floor);
	if (colors->has_floor)
		printf("Has Floor: true\n");
	else
		printf("Has Floor: false\n");
	printf("Ceiling RGB: [%d, %d, %d]\n",
		colors->rgb_ceiling[0], colors->rgb_ceiling[1], colors->rgb_ceiling[2]);
	// Print Hex value for ceiling
	printf("Ceiling Hex: 0x%X\n", colors->rgb_hex_ceiling);
	if (colors->has_ceiling)
		printf("Has Ceiling: true\n");
	else
		printf("Has Ceiling: false\n");
	if (colors->color_start_line)
		printf("Colors Start at line : [%ld]\n", colors->color_start_line);
}

void	print_grid(char **grid)
{
	size_t	row;
	size_t	row_count;

	row = 0;
	if (!grid)
	{
		printf("Grid is NULL\n");
		return ;
	}
	printf("start to print map grid\n");
	row_count = 0;
	while (grid[row_count] != NULL)
	{
		row_count++;
	}
	while (row < row_count)
	{
		printf("%s\n", grid[row]);
		row++;
	}
}

void	print_grid_character(char **grid)
{
	size_t	row;
	size_t	index;
	size_t	row_count;

	row = 0;
	index = 0;
	if (!grid)
		return (printf("Grid is NULL\n"), (void)0);
	row_count = 0;
	while (grid[row_count] != NULL)
		row_count++;
	printf("rowcount %ld\n", row_count);
	while (row < row_count)
	{
		printf("row:[%ld] ", row);
		index = 0;
		while (grid[row][index] != '\0')
		{
			printf("%c", grid[row][index]);
			index++;
		}
		printf("\n");
		row++;
	}
}

void	print_textures(t_textures *textures)
{
	printf("NO: %s\n", textures->no_texture);
	printf("SO: %s\n", textures->so_texture);
	printf("WE: %s\n", textures->we_texture);
	printf("EA: %s\n", textures->ea_texture);
	printf("Last texture line: %ld\n", textures->last_texture_line);
}

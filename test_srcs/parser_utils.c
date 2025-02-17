#include "../includes/parser.h"

void	print_grid(char **grid)
{
	size_t	row;

	row = 0;
	if (!grid)
	{
		printf("Grid is NULL\n");
		return;
	}
	while (grid[row])
	{
		printf("%s\n", grid[row]);
		row++;
	}
}

void	print_grid_character(char **grid)
{
	size_t	row;
	size_t	index;

	row = 0;
	index = 0;

	if (!grid)
	{
		printf("Grid is NULL\n");
		return;
	}
	while (grid[row])
	{
		printf("row:[%ld] ", row);
		while (grid[row][index] != '\0')
		{
			printf("%c", grid[row][index]);
			index++;
		}
		printf("\n");
		index = 0;
		row++;
	}
}

void free_grid(char **grid)
{
	size_t	row = 0;

	row = 0;
	if (!grid)
		return;
	while (grid[row])
	{
		free(grid[row]);
		row++;
	}
	free(grid);
}
#include "../includes/parser.h"

void print_grid(char **grid)
{
	size_t row;

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
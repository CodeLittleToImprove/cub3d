#include "../includes/parser.h"

void	print_grid(char **grid)
{
	size_t	row;
	size_t	row_count;

	row = 0;
	if (!grid)
	{
		printf("Grid is NULL\n");
		return;
	}

	row_count = 0;
	while (grid[row_count] != NULL)
	{
		row_count++;
	}

	while (row < row_count - 1)
	{
		printf("%s\n", grid[row]);
		row++;
	}
}

void print_grid_character(char **grid)
{
	size_t	row = 0;
	size_t	index = 0;
	size_t	row_count;

	if (!grid)
	{
		printf("Grid is NULL\n");
		return;
	}

	row_count = 0;
	while (grid[row_count] != NULL)
	{
		row_count++;
	}

	while (row < row_count - 1)
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

void	free_grid(char **grid)
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

bool	is_empty_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_isspace(line[i]))
			return (false);
		i++;
	}
	return (true);
}



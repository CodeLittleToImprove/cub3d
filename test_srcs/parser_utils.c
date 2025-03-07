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

	while (row < row_count)
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

size_t	count_leading_white_space(char *line)
{
	size_t	count;

	count = 0;
	while (ft_isspace(line[count]))
	{
		count++;
	}
	return (count);
}

char	*skip_empty_lines(int fd, size_t *empty_lines)
{
	char	*line;

	line = get_next_line(fd);
	while (line && is_empty_line(line))
	{
		(*empty_lines)++;
		// printf("empty_lines: %ld\n", *empty_lines);
		free(line);
		line = get_next_line(fd);
	}
	return (line); // Returns the first non-empty line or NULL if EOF
}

char	*trim_space_and_copy(char *line, size_t width)
{
	size_t	leading_spaces;
	char	*trimmed_line;

	leading_spaces = count_leading_white_space(line);
	trimmed_line = malloc((width + 1) * sizeof(char));
	if (!trimmed_line)
	{
		perror("Memory allocation failed");
		return (NULL);
	}
	ft_strlcpy(trimmed_line, line + leading_spaces, width + 1);
	return (trimmed_line);
}

void	detect_player_pos(t_map *map)
{
	size_t	column;
	size_t	max_height;
	size_t row;

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
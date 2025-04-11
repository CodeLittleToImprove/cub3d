#include "../../includes/parser.h"

static bool	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

static bool	update_player_count(char c, size_t *player_count)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*player_count)++;
		if (*player_count > 1)
		{
			printf("Error: Multiple player start positions found.\n");
			return (false);
		}
	}
	return (true);
}

static bool	is_valid_file_content(int fd, size_t *player_count)
{
	char	c;

	while (read(fd, &c, 1) == 1)
	{
		if (c == '\n')
			continue ;
		if (!is_valid_char(c))
		{
			printf("Invalid character found: '%c'\n", c);
			// remove in final parser
			return (false);
		}
		if (!update_player_count(c, player_count))
			return (false);
	}
	return (true);
}

bool	has_valid_characters_only(char *file_name)
{
	int		fd;
	size_t	player_count;
	bool	file_is_valid;

	fd = open_input_file(file_name);
	if (fd <= 0)
		return (false);
	player_count = 0;
	file_is_valid = is_valid_file_content(fd, &player_count);
	close(fd);
	if (file_is_valid && player_count == 0)
	{
		file_is_valid = false;
		printf("Error: No player start position found.\n");
		// remove in final parser
	}
	return (file_is_valid);
}

char	**copy_grid(char **grid, size_t height)
{
	char	**new_grid;
	size_t	i;

	new_grid = malloc(sizeof(char *) * (height + 1));
	i = 0;
	if (!new_grid)
		return (NULL);
	while (i < height)
	{
		new_grid[i] = ft_strdup(grid[i]);
		if (!new_grid[i])
		{
			while (i > 0)
				free(new_grid[--i]);
			free(new_grid);
			return (NULL);
		}
		i++;
	}
	new_grid[i] = NULL;
	return (new_grid);
}

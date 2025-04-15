#include "../../includes/parser.h"

static void	init_width_vars(size_t *current_line, size_t *width,
			bool *found_first_char)
{
	*current_line = 0;
	*width = 0;
	*found_first_char = false;
}

static size_t	handle_error_and_clean_size(char *line, int fd)
{
	if (line)
		free(line);
	if (fd >= 0)
		close(fd);
	return (0);
}

size_t	count_width(char *file_name, size_t row)
{
	int		fd;
	size_t	current_line;
	size_t	width;
	char	c;
	bool	found_first_char;

	fd = open_input_file(file_name);
	if (fd <= 0)
		return (0);
	init_width_vars(&current_line, &width, &found_first_char);
	while (read(fd, &c, 1) == 1)
	{
		if (c == '\n' && current_line++ == row)
			break ;
		if (current_line == row)
		{
			if (!found_first_char && ft_isspace(c))
				continue ;
			found_first_char = true;
			if (width == MAX_MAP_WIDTH)
				return (close(fd), 0);
			width++;
		}
	}
	return (close(fd), width);
}

size_t	count_height_and_free(char *file_name)
{
	int			fd;
	char		*line;
	size_t		height;

	fd = open_input_file(file_name);
	if (fd <= 0)
		return (0);
	line = get_next_line(fd);
	height = 0;
	if (line == NULL)
		return (0);
	while (line != NULL)
	{
		if (is_empty_line(line) || height == MAX_MAP_HEIGHT)
			return (handle_error_and_clean_size(line, fd));
		height++;
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), height);
}

bool	init_map_height(char *file_name, t_map *map)
{
	size_t	height;

	height = count_height_and_free(file_name);
	if (height == 0)
	{
		map->max_height = 0;
		return (false);
	}
	map->max_height = height;
	return (true);
}

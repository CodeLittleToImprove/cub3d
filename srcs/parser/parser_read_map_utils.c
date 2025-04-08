#include "../../includes/parser.h"

static void	init_width_vars(size_t *current_line, size_t *width,
			bool *found_first_char)
{
	*current_line = 0;
	*width = 0;
	*found_first_char = false;
}

size_t	count_width(char *file_name, size_t row, t_map *map)
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
			width++;
		}
	}
	if (width > map->max_width)
		map->max_width = width;
	return (close(fd), width);
}

size_t	count_height_and_free(char *file_name)
{
	int			fd;
	char		*line;
	size_t		height;

	fd = open(file_name, O_RDONLY, 0);
	//	if (fd <= 0)
	//	//		ft_error_and_exit("file does not exist or no permission");
	line = get_next_line(fd);
	height = 0;
	if (line == NULL)
		return (0);
	while (line != NULL)
	{
		if (is_empty_line(line))
		{
			free(line);
			close(fd);
			return (0);
		}
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

bool	init_map_height(char *file_name, t_map *map)
{
	map->max_height = count_height_and_free(file_name);
	return (map->max_height > 0);
}

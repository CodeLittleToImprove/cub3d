#include "../includes/parser.h"

bool is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

bool	has_valid_characters_only(char *file_name)
{
	int		fd;
	bool	file_is_valid;
	char	c;

	fd = open(file_name, O_RDONLY, 0);
	file_is_valid = true;
	if (fd <= 0)
	{
		perror("file does not exist or no permission");
		return (false);
	}
	while (read(fd, &c, 1) == 1)
	{
		// Newline characters are allowed in the file
		if (c == '\n')
			continue;
		if (!is_valid_char(c))
		{
			file_is_valid = false;
			printf("Invalid character found: '%c'\n", c); // not in final parser
			break;
		}
	}
	close(fd);
	return (file_is_valid);
}

size_t	count_width(char *file_name, size_t row)
{
	int		fd;
	size_t	current_line;
	size_t	width;
	char	c;

	fd = open(file_name, O_RDONLY, 0);
	if (fd <= 0)
		perror("file does not exist or no permission");
	current_line = 0;
	width = 0;

	while (read(fd, &c, 1) == 1)
	{
	if (c == '\n')
	{
		if (current_line == row)
			break;
		current_line++;
		continue; // Don't count newline characters
	}
	if (current_line == row)
		width++;
	}
	close(fd);
	return (width);
}

size_t	count_height_and_free(char *file_name)
{
	int			fd;
	char		*line;
	size_t		height;

	fd = open(file_name, O_RDONLY, 0);
//	if (fd <= 0)
//		ft_error_and_exit("file does not exist or no permission");
	line = get_next_line(fd);
	height = 0;
	if (line == NULL)
		return (0);
	while (line != NULL)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

char	**create_grid(char *file_name)
{
	size_t	height;
	char	**grid;

	height = count_height_and_free(file_name);
	printf("height : %ld\n", height);
	grid = malloc((height + 1) * sizeof(char *));
//	if (!grid)
//	{
//		perror("Memory allocation failed");
//		return (NULL);
//	}
	int		fd;
	char	*line;
	size_t	width;
	size_t	row = 0;
	fd = open(file_name, O_RDONLY, 0);
	while (row < height)
	{
		line = get_next_line(fd); // small problem with the last character did not get read properly when there is no \n at the end
		if (!line)
			break;
		width = count_width(file_name, row);
		printf("width : %ld\n", width);
		grid[row] = malloc((width + 1) * sizeof(char));
		// printf("strlen line before copying: %d\n", strlen (line));
		// if (line[strlen(line) - 1] == '\n')
		// {
		// 	// printf("detected new line \n");
		// 	line[strlen(line) - 1] = '\0';
		// }
		ft_strlcpy(grid[row], line, width + 1);
		// printf("strlen line after copying: %d\n", strlen (grid[row]));
		free(line);
		row++;
	}
	close(fd);
	return (grid);
}

void	read_map_file(char *file_name, t_map *map)
{
	int		y;
	int		fd;
	char	*line;
	char	*next_line;

	if (has_valid_characters_only(file_name) == false)
	{
		printf("file contains not valid characters \n");
		exit (-1);
	}

	map->grid = create_grid(file_name);
	// print_grid(map->grid);
	print_grid_character(map->grid);
//	map->matrix = allocate_matrix(file_name);
//	fd = open(file_name, O_RDONLY, 0);
//	y = 0;
//	line = get_next_line(fd);
//	next_line = NULL;
//	while (line != NULL)
//	{
//		next_line = get_next_line(fd);
//		get_dots_from_line(line, data->matrix, y);
//		y++;
//		free(line);
//		line = next_line;
//	}
//	map->matrix[y] = NULL;
//	close(fd);
}

int	main(int argc, char *argv[])
{
	t_map	map;

	if (argc != 2)
		return (-1);
	read_map_file(argv[1], &map);
//	printf("max Map Width: %d\n", map.width);
//	printf("max Map Height: %d\n", map.height);
}
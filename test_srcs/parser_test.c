#include "../includes/parser.h"

bool is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

size_t	count_width_and_free(char *file_name, size_t row)
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
	if (is_valid_char(c)  && current_line == row)
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

//t_map	**allocate_matrix(char *file_name)
//{
//	t_map	**allocated_matrix;
//	size_t	x;
//	size_t	y;
//
//	x = count_width_and_free(file_name);
//	y = count_height_and_free(file_name);
//	allocated_matrix = (t_map **) ft_calloc(sizeof(t_map *), (y + 1));
////	if (!allocated_matrix)
////		ft_error_and_exit("Memory allocation failed");
//	while (y > 0)
//	{
//		allocated_matrix[y - 1] = (t_map *) ft_calloc(sizeof(t_map), x);
//		y--;
//	}
//	return (allocated_matrix);
//}

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
		line = get_next_line(fd);
		if (!line)
			break;
		width = count_width_and_free(file_name, row);
		printf("width : %ld\n", width);
		grid[row] = malloc((width + 1) * sizeof(char));
		ft_strlcpy(grid[row], line, strlen(line));
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

	map->grid = create_grid(file_name);
	print_grid(map->grid);
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
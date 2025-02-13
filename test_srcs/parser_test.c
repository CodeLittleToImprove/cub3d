#include "../includes/parser.h"

size_t	count_width_and_free(char *file_name)
{
	int		fd;
	char	*line;
	size_t	width;

	fd = open(file_name, O_RDONLY, 0);
//	if (fd <= 0)
//		ft_error_and_exit("file does not exist or no permission");
	line = get_next_line(fd);
//	if (line == NULL)
//		handle_empty_or_null_line(line, fd);
	width = ft_count_words(line, ' ');
	free(line);
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
	height = count_height_and_free(file_name);
	printf("height : %d\n", height);
	char	**grid = malloc((height + 1) * sizeof(char *));
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
		width = ft_count_words(line, ' ');
		printf("width : %d\n", width);
		grid[row] = malloc((width + 1) * sizeof(char));
//		ft_strlcpy(grid[row], line, strlen(line));
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

	map->matrix = create_grid(file_name);
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
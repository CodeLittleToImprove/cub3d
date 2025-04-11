#include "../../includes/parser.h"

static int	*get_color_array(t_colors *colors, char type)
{
	if (type == 'F')
		return (colors->rgb_floor);
	if (type == 'C')
		return (colors->rgb_ceiling);
	return (NULL);
}

bool	parse_color(char *line, t_colors *colors, char type)
{
	size_t	i;
	size_t	index;
	char	*token;
	char	*save_ptr;
	int		*color_array;

	i = 0;
	index = 0;
	i = skip_leading_chars(line, i, &type);
	color_array = get_color_array(colors, type);
	if (color_array == NULL)
		return (false);
	// printf("parse color line %s\n", line);
	// printf("first character of line %c\n", line[i]);
	// printf("start_color_pos: %ld\n", start_color_pos);
	token = ft_strtok_r(&line[i], ",", &save_ptr);
	// printf("first token:%s\n", token);
	while (token && index < 3)
	{
		if (!is_valid_rgb(token))
			return (printf("Error: Invalid RGB value: %s\n", token), false);
		color_array[index] = ft_atoi(token);
		token = ft_strtok_r(NULL, ",", &save_ptr);
		index++;
	}
	if (index != 3 || token != NULL)
		return (printf("Error: Too many values\n"), false);
	return (true);
}

bool	check_and_parse_color(char *line, t_colors *colors,
			char type, bool *found_flag)
{
	if (!(*found_flag) && ft_strchr(line, type))
	{
		// if (type == 'F')
		// 	printf("Detected potential floor color in file\n");
		// else if (type == 'C')
		// 	printf("Detected potential ceiling color in file\n");
		if (parse_color(line, colors, type))
		{
			// if (type == 'F')
			// 	printf("Floor color successfully extracted\n");
			// else if (type == 'C')
			// 	printf("Ceiling color successfully extracted\n");
			*found_flag = true;
			return (true);
		}
	}
	return (false);
}

static void	mark_first_color_line(t_colors *colors,
		size_t line_number)
{
	if (!(colors->first_color_found))
	{
		colors->color_start_line = line_number;
		printf("color_start_line is %ld\n", colors->color_start_line);
		colors->first_color_found = true;
	}
	// if (!colors->has_floor || !colors->has_ceiling)
	// {
	// 	colors->color_end_line = line_number;
	// 	printf("color_end_line is %ld\n", colors->color_end_line);
	// }
}

bool	detect_color(const char *filename, t_colors *colors)
{
	int		fd;
	char	*line;
	size_t	line_number;

	fd = open_input_file(filename);
	line = get_next_line(fd);
	line_number = 0;
	set_default_values_color(colors);
	while (line != NULL)
	{
		if (!validate_color_line(line, line_number, fd, colors))
			return (free(line), false);
		if (check_and_parse_color(line, colors, 'F', &colors->has_floor)
			|| check_and_parse_color(line, colors, 'C', &colors->has_ceiling))
			mark_first_color_line(colors, line_number);
		if (colors->has_floor && colors->has_ceiling
			&& colors->found_both_colors == false)
			colors->found_both_colors = true;
		free(line);
		line = get_next_line(fd);
		line_number++;
	}
	close(fd);
	return (colors->has_floor && colors->has_ceiling);
}

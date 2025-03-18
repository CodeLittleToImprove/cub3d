#include "../includes/parser.h"

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
	size_t	j;
	char	*token;
	char	*save_ptr;
	int		*color_array;

	i = 0;
	j = 0;
	i = skip_leading_chars(line, i, &type);
	color_array = get_color_array(colors, type);
	if (color_array == NULL)
		return (false);
	// printf("parse color line %s\n", line);
	// printf("first character of line %c\n", line[i]);
	// printf("start_color_pos: %ld\n", start_color_pos);
	// printf("i : %ld\n", i);
	token = ft_strtok_r(&line[i],",", &save_ptr);
	// printf("first token:%s\n", token);
	while(token && j < 3)
	{
		if (!is_valid_rgb(token))
			return (printf("Error: Invalid RGB value: %s\n", token), false);
		int temp = ft_atoi(token); // only for debugging
		// printf("temp : %ld\n", temp);
		color_array[j] = temp;
		token = ft_strtok_r(NULL,",", &save_ptr);
		// printf("token:%s\n", token);
		j++;
	}
	if (j != 3|| token != NULL)
		return (printf("Error: Too many values\n"), false);
	return (true);
}

bool	check_and_parse_color(char *line, t_colors *colors, char type, bool *found_flag)
{
	if (!(*found_flag) && ft_strchr(line, type))
	{
		if (type == 'F')
			printf("Detected potential floor color in file\n");
		else if (type == 'C')
			printf("Detected potential ceiling color in file\n");

		if (parse_color(line, colors, type))
		{
			if (type == 'F')
				printf("Floor color successfully extracted\n");
			else if (type == 'C')
				printf("Ceiling color successfully extracted\n");
			*found_flag = true;
			return (true);
		}
	}
	return (false);
}

bool	detect_color(const char *filename, t_colors *colors)
{
	int		fd;
	char	*line;
	bool	found_floor;
	bool	found_ceiling;
	bool	first_color_found;
	size_t	line_number;

	fd = open_input_file(filename);
	if (fd < 0)
		return (false);
	line = get_next_line(fd);
	// printf("line in detect color:%s\n", line);
	set_default_values_color(colors);
	found_floor = false;
	found_ceiling = false;
	first_color_found = false;
	line_number = 0;
	while (line!= NULL)
	{
		if (first_color_found && is_invalid_color_line(line))
		{
			printf("Error: Found non-color line within color definitions at line %ld: %s\n", line_number, line);
			free(line);
			close(fd);
			return (false);
		}
		if (check_and_parse_color(line, colors, 'F', &found_floor) ||
				check_and_parse_color(line, colors, 'C', &found_ceiling))
		{
			if (!first_color_found)
			{
				colors->color_start_line = line_number;
				first_color_found = true;
			}
		}
		free(line);
		if (found_floor && found_ceiling)
			return (true);
		line = get_next_line(fd);
		line_number++;
	}
	close(fd);
	return (false);
}
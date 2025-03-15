#include "../includes/parser.h"

bool	is_valid_rgb(char *str)
{
	int	num;
	size_t	i;

	num = 0;
	i = 0;
	i = skip_leading_chars(str, i, " ");
	// printf("str:%s\n", str);
	while (str[i] && ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - '0');
		if (num > 255)
		{
			printf("num %d is too large\n", num);
			return (false);
		}
		i++;
	}
	// printf("pre skip in valid rgb i:%d\n", i);
	i = skip_leading_chars(str, i, " ");
	// printf("in valid rgb i:%d\n", i);
	if (str[i] == '\0' || str[i] == '\n')
		return (true);
	return (false);
}

char	*ft_strtok_r(char *str, char *delim, char **saveptr)
{
	char	*token_start;

	if (str)
		*saveptr = str;
	if (!*saveptr)
		return (NULL);
	while (**saveptr && strchr(delim, **saveptr))
		(*saveptr)++;
	if (!**saveptr)
		return (NULL);
	token_start = *saveptr;
	while (**saveptr && !strchr(delim, **saveptr))
		(*saveptr)++;
	if (**saveptr)
	{
		**saveptr = '\0';
		(*saveptr)++;
	}
	return (token_start);
}

size_t	skip_leading_chars(char *str, size_t i, char *skip_chars)
{
	while (str[i] && ft_strchr(skip_chars, str[i]))
		i++;
	return (i);
}

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
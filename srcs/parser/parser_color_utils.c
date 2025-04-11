#include "../../includes/parser.h"

bool	is_valid_rgb(char *str)
{
	int		num;
	size_t	i;

	num = 0;
	i = 0;
	i = skip_leading_chars(str, i, " ");
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
	i = skip_leading_chars(str, i, " ");
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
	char	*char_to_skip_str;

	char_to_skip_str = malloc(sizeof(char) * 2);
	char_to_skip_str[0] = skip_chars[0];
	char_to_skip_str[1] = '\0';
	while (str[i] && ft_strchr(char_to_skip_str, str[i]))
		i++;
	free(char_to_skip_str);
	return (i);
}

bool	is_invalid_color_line(char *line)
{
	if (is_empty_line(line))
		return (false);
	if (!(ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0))
		return (true);
	return (false);
}

bool	validate_color_line(char *line, size_t line_number,
	int fd, t_colors *colors)
{
	if ((ft_strncmp(line, "F", 1) == 0 && colors->has_floor)
		|| (ft_strncmp(line, "C", 1) == 0 && colors->has_ceiling))
	{
		printf("Error: Duplicate color declaration at line %ld: %s\n",
			line_number, line);
		close(fd);
		return (false);
	}
	if ((ft_strncmp(line, "F", 1) == 0
			|| ft_strncmp(line, "C", 1) == 0) && colors->found_both_colors)
	{
		printf("Error: Already found both colors, duplicate at line %ld: %s\n",
			line_number, line);
		close(fd);
		return (false);
	}
	if (colors->first_color_found && is_invalid_color_line(line)
		&& !colors->found_both_colors)
	{
		printf("Error: Found non-color line within "
			"color definitions at line %ld: %s\n", line_number, line);
		close(fd);
		return (false);
	}
	return (true);
}

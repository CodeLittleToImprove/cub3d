#include "../includes/parser.h"

void	set_default_values_color(t_colors *colors)
{
	colors->rgb_floor[0] = 0;
	colors->rgb_floor[1] = 0;
	colors->rgb_floor[2] = 0;
	colors->rgb_ceiling[0] = 0;
	colors->rgb_ceiling[1] = 0;
	colors->rgb_ceiling[2] = 0;
	colors->has_floor = false; // probably not needed
	colors->has_ceiling = false; // probably not needed
	colors->color_start_line = 0;
}

bool	is_valid_rgb(char *str)
{
	int	num;
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
	while (str[i] && ft_strchr(skip_chars, str[i]))
		i++;
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
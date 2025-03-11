#include "../includes/parser.h"

bool	is_valid_rgb(char *str)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		num = num * 10 + (str[i] - '0');
		i++;
		if (num > 255)
			return (false);
	}
	return (i > 0);
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
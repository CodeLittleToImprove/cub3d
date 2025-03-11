#include "../includes/parser.h"

bool	is_valid_rgb(char *str)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	i = skip_leading_chars(str, i, " ");
	printf("str:%s\n", str);
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
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

// next step initialize color struct with default values
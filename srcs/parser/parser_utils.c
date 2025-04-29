#include "../../includes/parser.h"

bool	is_empty_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_isspace(line[i]))
			return (false);
		i++;
	}
	return (true);
}

size_t	count_leading_white_space(char *line)
{
	size_t	count;

	count = 0;
	while (ft_isspace(line[count]))
	{
		count++;
	}
	return (count);
}

char	*skip_empty_lines(int fd, size_t *empty_lines)
{
	char	*line;

	line = get_next_line(fd);
	while (line && is_empty_line(line))
	{
		(*empty_lines)++;
		free(line);
		line = get_next_line(fd);
	}
	return (line); // Returns the first non-empty line or NULL if EOF
}

char	*trim_space_and_copy(char *line, size_t width)
{
	size_t	leading_spaces;
	char	*trimmed_line;

	leading_spaces = count_leading_white_space(line);
	trimmed_line = malloc((width + 1) * sizeof(char));
	if (!trimmed_line)
	{
		perror("Memory allocation failed");
		return (NULL);
	}
	ft_strlcpy(trimmed_line, line + leading_spaces, width + 1);
	return (trimmed_line);
}

bool	is_cub_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
	{
		printf("Error wrong file Extension, use .cub");
		return (false);
	}
	return (true);
}
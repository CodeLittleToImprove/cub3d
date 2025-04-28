#include "../../includes/parser.h"

bool	is_invalid_texture_line(char *line)
{
	if (is_empty_line(line))
		return (false);
	if (!(ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
			||ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0))
		return (true);
	return (false);
}

bool	is_valid_texture_path(char *path)
{
	int	fd;

	//	printf("path in is valid texture path:%s\n", path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: opening texture file\n");
		return (false);
	}
	close(fd);
	return (true);
}

bool	is_texture_identifier(char *line)
{
	if (!line)
		return (false);
	if (ft_strncmp(line, "NO", 2) == 0)
		return (true);
	if (ft_strncmp(line, "SO", 2) == 0)
		return (true);
	if (ft_strncmp(line, "WE", 2) == 0)
		return (true);
	if (ft_strncmp(line, "EA", 2) == 0)
		return (true);
	return (false);
}

bool	is_duplicate_texture_line(char *line, size_t line_number,
			t_textures *textures, int fd)
{
	if (line_number > textures->last_texture_line && textures->all_set)
	{
		if (is_texture_identifier(line))
		{
			printf("DEBUG: Detected duplicate texture"
				"assignment at line %s\n", line);
			return (handle_texture_error_and_clean(line, fd));
		}
	}
	return (true);
}

char	*extract_texture_path(char *line, char *key)
{
	char	*raw_path;
	char	*trimmed_path;

	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, key, ft_strlen(key)) != 0)
		return (NULL);
	line += ft_strlen(key);
	while (*line == ' ' || *line == '\t')
		line++;
	raw_path = ft_strdup(line);
	if (!raw_path)
	{
		printf("Error: Memory allocation failed\n");
		return (NULL);
	}
	// printf("raw_path %s\n", raw_path);
	trimmed_path = ft_strtrim(raw_path, " \n");
	if (!trimmed_path)
	{
		free(trimmed_path);
		return (NULL);
	}
	// printf("trimmed_path %s\n", trimmed_path);
	free(raw_path);
	return (trimmed_path);
}

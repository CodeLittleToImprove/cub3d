#include "../includes/parser.h"

bool	is_invalid_texture_line(char *line)
{
	if (is_empty_line(line))
		return (false);
	if (!(ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0 ||
		ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0))
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
		perror("Error opening texture file");
		return (false);
	}
	close(fd);
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
	// printf("trimmed_path %s\n", trimmed_path);
	free(raw_path);
	return (trimmed_path);
}

void	set_default_values_textures(t_textures *textures)
{
	textures->no_texture = NULL;
	textures->so_texture = NULL;
	textures->we_texture = NULL;
	textures->ea_texture = NULL;
	textures->no_set = false;
	textures->so_set = false;
	textures->we_set = false;
	textures->ea_set = false;
	textures->last_texture_line = 0;
}
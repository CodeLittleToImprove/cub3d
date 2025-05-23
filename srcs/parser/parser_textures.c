#include "../../includes/parser.h"

bool	assign_texture_path(char *line, char *key,
							char **texture_path, bool *valid_texture)
{
	if (*valid_texture)
	{
		// printf("Error: Duplicate texture assignment for %s\n", key);
		return (false);
	}
	*texture_path = extract_texture_path(line, key);
	if (!*texture_path)
	{
		// printf("Error: Failed to extract texture path for %s\n", key);
		return (false);
	}
	// printf("Extracted texture path for %s: %s\n", key, *texture_path);
	if (**texture_path == '\0')
	{
		printf("Error: Extracted texture path for %s is empty.\n", key);
		free(*texture_path);
		*texture_path = NULL;
		return (false);
	}
	if (!is_valid_texture_path(*texture_path))
	{
		printf("Error: Texture file for %s is invalid or does not exist: %s\n", key, *texture_path);
		free(*texture_path);
		*texture_path = NULL;
		return (false);
	}
	*valid_texture = true;
	// printf("Successfully assigned texture: %s -> %s\n", key, *texture_path);
	// printf("Key [%s] Valid_texture boolean assigned texture: %d\n", key, *valid_texture);
	return (true);
}

bool	process_texture_line(char *line, t_textures *textures)
{
	bool	success_assign;

	success_assign = true;
	if (ft_strncmp(line, "NO", 2) == 0)
		success_assign = assign_texture_path(line, "NO",
				&textures->no_texture, &textures->no_set);
	else if (ft_strncmp(line, "SO", 2) == 0)
		success_assign = assign_texture_path(line, "SO",
				&textures->so_texture, &textures->so_set);
	else if (ft_strncmp(line, "WE", 2) == 0)
		success_assign = assign_texture_path(line, "WE",
				&textures->we_texture, &textures->we_set);
	else if (ft_strncmp(line, "EA", 2) == 0)
		success_assign = assign_texture_path(line, "EA",
				&textures->ea_texture, &textures->ea_set);
	return (success_assign);
}

static bool	handle_invalid_texture_line(char *line,
			t_textures *textures, size_t line_number)
{
	if (!textures->all_set && is_invalid_texture_line(line)
		&& (textures->no_set || textures->so_set
			|| textures->we_set || textures->ea_set))
	{
		printf("Error: Found non-texture line within texture"
			" definitions at line %ld: %s\n", line_number, line);
		return (false);
	}
	return (true);
}

static void	mark_all_textures_set(t_textures *textures,
			size_t line_number)
{
	textures->last_texture_line = line_number;
	textures->all_set = true;
}

bool	detect_textures(char *filename, t_textures *textures)
{
	int		fd;
	char	*line;
	size_t	line_number;

	fd = open_input_file(filename);
	line = get_next_line(fd);
	line_number = 0;
	while (line != NULL)
	{
		if (!handle_invalid_texture_line(line, textures, line_number))
			return (handle_texture_error_and_clean(line, fd));
		if (!process_texture_line(line, textures))
			return (handle_texture_error_and_clean(line, fd));
		// printf("DEBUG: no_set=%d, so_set=%d, we_set=%d, ea_set=%d\n",
		// textures->no_set, textures->so_set, textures->we_set, textures->ea_set);
		free(line);
		if (textures->no_set && textures->so_set
			&&textures->we_set && textures->ea_set && !textures->all_set)
			mark_all_textures_set(textures, line_number);
		line = get_next_line(fd);
		line_number++;
		if (!is_duplicate_texture_line(line, line_number, textures, fd))
			return (false);
	}
	// printf("FINAL DEBUG: no_set=%d, so_set=%d, we_set=%d, ea_set=%d\n",
	// 	textures->no_set, textures->so_set, textures->we_set, textures->ea_set);
	return (close(fd), textures->no_set && textures->so_set
		&& textures->we_set && textures->ea_set);
}

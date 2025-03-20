#include "../includes/parser.h"

bool	assign_texture_path(char *line, char *key, char **texture_path, bool *valid_texture)
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

bool	process_texture_line(char *line, size_t line_number, t_textures *textures)
{
	if (assign_texture_path(line, "NO", &textures->no_texture, &textures->no_set) ||
		assign_texture_path(line, "SO", &textures->so_texture, &textures->so_set) ||
		assign_texture_path(line, "WE", &textures->we_texture, &textures->we_set) ||
		assign_texture_path(line, "EA", &textures->ea_texture, &textures->ea_set))
	{
		// printf("DEBUG texture detected on line %ld: %s\n", line_number, line);
		return (true);
	}
	return (false);
}

bool	detect_textures(char *filename, t_textures *textures)
{
	int		fd;
	char	*line;
	size_t	line_number;
	fd = open_input_file(filename);
	set_default_values_textures(textures);
	line = get_next_line(fd);
	line_number = 0;
	while (line != NULL)
	{
		if (is_invalid_texture_line(line) &&
			(textures->no_set || textures->so_set || textures->we_set || textures->ea_set))
		{
			printf("Error: Found non-texture line within texture definitions at line %ld: %s\n", line_number, line); //buggy when something is writtten in between of color
			free(line);
			close(fd);
			return (false);
		}
		process_texture_line(line, line_number, textures);
		// printf("DEBUG: no_set=%d, so_set=%d, we_set=%d, ea_set=%d\n",
		// textures->no_set, textures->so_set, textures->we_set, textures->ea_set);
		free(line);
		if (textures->no_set && textures->so_set && textures->we_set && textures->ea_set)
		{
			textures->last_texture_line = line_number;
			break;
		}
		line = get_next_line(fd);
		line_number++;
	}
	close(fd);
	// printf("FINAL DEBUG: no_set=%d, so_set=%d, we_set=%d, ea_set=%d\n",
	// 	textures->no_set, textures->so_set, textures->we_set, textures->ea_set);
	return (textures->no_set && textures->so_set && textures->we_set && textures->ea_set);
}
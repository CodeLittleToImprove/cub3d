#include "../../includes/parser.h"

void	set_default_values_map(t_map *map)
{
	map->max_height = 0;
	map->max_width = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = '\0';
	map->map_end_line = 0;
}

bool	write_and_track_last_line(int fd_out, const char *line, char **last_map_line)
{
	write(fd_out, line, ft_strlen(line));

	// If the line doesn't end with a newline, it's the last map line
	if (line[ft_strlen(line) - 1] != '\n')
	{
		*last_map_line = malloc(ft_strlen(line) + 1);
		if (!*last_map_line)
			return (false);
		ft_strlcpy(*last_map_line, line, ft_strlen(line) + 1);
		// printf("DEBUG: This should be the last line: %s\n", *last_map_line);
	}
	return (true);
}

static bool	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

bool	has_valid_characters_only(char *file_name)
{
	int		fd;
	bool	file_is_valid;
	char	c;
	size_t	player_count;

	fd = open(file_name, O_RDONLY, 0);
	file_is_valid = true;
	player_count = 0;
	if (fd <= 0)
		return(perror("file does not exist or no permission"),false);
	while (read(fd, &c, 1) == 1)
	{
		if (c == '\n')
			continue;
		if (!is_valid_char(c))
		{
			file_is_valid = false;
			printf("Invalid character found: '%c'\n", c); // remove in final parser
			break;
		}
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			player_count++;
		if (player_count > 1)
		{
			file_is_valid = false;
			printf("Error: Multiple player start positions found.\n");
			break;
		}
	}
	if (player_count == 0)
	{
		file_is_valid = false;
		printf("Error: No player start position found.\n");
	}
	close(fd);
	return (file_is_valid);
}

bool	is_valid_start_or_end_line(const char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (false);
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}
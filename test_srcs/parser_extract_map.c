#include "../includes/parser.h"

bool	detect_map_start(char *line, bool *has_map_started, bool *is_valid_start)
{
	if (!*has_map_started && is_valid_map_line(line))
	{
		// printf("DEBUG: First map line detected: %s\n", line);
		*has_map_started = true;
		*is_valid_start = is_valid_start_or_end_line(line);
	}

	// Detect an empty line after the map starts
	if (*has_map_started && is_empty_line(line))
	{
		printf("Detected empty line after map start.\n");
		return (false);
	}
	return (true);
}

int	process_map(int fd_in, int fd_out, t_map *map)
{
	char	*line;
	char	*last_map_line;
	bool	has_map_started;
	bool	is_valid_start;
	bool	is_valid_end;

	line = get_next_line(fd_in);
	if (line == NULL)
		exit(-1);
	has_map_started = false;
	is_valid_start = false;
	is_valid_end = false;
	set_default_values_map(map);
	// printf("before increase map end line %ld\n", map->map_end_line);
	while (line != NULL)
	{
		if (!detect_map_start(line, &has_map_started, &is_valid_start))
		{
			return(free(line), -1);
		}
		if (has_map_started && is_valid_start)
		{
			if (!write_and_track_last_line(fd_out, line, &last_map_line))
			{
				return(free(line), -1);
			}
		}
		free(line);
		line = get_next_line(fd_in);
		map->map_end_line++;
	}
	if (last_map_line && is_valid_start_or_end_line(last_map_line))
		is_valid_end = true;
	if (has_map_started && is_valid_start && is_valid_end)
	{
		// printf("after increase map end line %ld\n", map->map_end_line); // it's + 1 after the last line
		// printf("map contains properly start and ending\n");
		return (0);
	}
	return (-1);
}

bool	extract_map(const char *filename, t_map *map)
{
	int		fd_in;
	int		fd_out;

	fd_in = open_input_file(filename);
	fd_out = open_output_file("temp_map.cub");
	if (process_map(fd_in, fd_out, map) == -1)
	{
		printf("debug: map invalid before copying\n");
		//delete temp map cub later
		return (false);
	}
	close(fd_in);
	close(fd_out);
	return (true);
}
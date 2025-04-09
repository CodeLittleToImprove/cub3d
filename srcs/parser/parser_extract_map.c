#include "../../includes/parser.h"

bool	detect_map_start(char *line, t_map_state *state)
{
	// printf("DEBUG: detect map start line for debug: %s\n", line);
	if (!state->has_map_started && is_valid_map_line(line))
	{
		printf("DEBUG: First map line detected: %s\n", line);
		state->has_map_started = true;
		state->is_valid_start = is_valid_start_or_end_line(line);
		// printf("DEBUG: is valid start: %d\n", state->is_valid_start);
	}
	// Detect an empty line after the map starts
	if (state->has_map_started && is_empty_line(line))
	{
		printf("Map starts with empty line debug printf %s\n", line);
		printf("Detected empty line after map start.\n");
		return (false);
	}
	return (true);
}

bool	process_line(char *line, t_map_state *state, int fd_out)
{
	if (!detect_map_start(line, state))
		return (false);
	if (state->has_map_started && state->is_valid_start
		&&is_valid_map_line(line))
	{
		if (!write_and_track_last_line(fd_out, line, state))
			return (false);
	}
	return (true);
}

static void	init_map_variables(t_map_state *state, t_map *map)
{
	state->last_map_line = NULL;
	state->has_map_started = false;
	state->is_valid_start = false;
	state->is_valid_end = false;
	set_default_values_map(map);
}

int	process_map(int fd_in, int fd_out, t_map *map)
{
	char		*line;
	t_map_state	state;

	line = get_next_line(fd_in);
	if (line == NULL)
		exit(-1);
	init_map_variables(&state, map);
	while (line != NULL)
	{
		if (!process_line(line, &state, fd_out))
			return (free(line), -1);
		if (is_valid_map_line(line))
			map->map_end_line++;
		free(line);
		line = get_next_line(fd_in);
	}
	if (state.last_map_line && is_valid_start_or_end_line(state.last_map_line))
		state.is_valid_end = true;
	free(state.last_map_line);
	if (state.has_map_started && state.is_valid_start && state.is_valid_end)
		return (0);
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

#include "../../includes/parser.h"

bool	write_and_track_last_line(int fd_out, char *line,
			t_map_state *state)
{
	write(fd_out, line, ft_strlen(line));
	// If the line doesn't end with a newline, it's the last map line
	if (line[ft_strlen(line) - 1] != '\n')
	{
		state->last_map_line = malloc(ft_strlen(line) + 1);
		if (!state->last_map_line)
			return (false);
		ft_strlcpy(state->last_map_line, line, ft_strlen(line) + 1);
		printf("\nDEBUG: This should be the last line: %s\n", state->last_map_line);
	}
	return (true);
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

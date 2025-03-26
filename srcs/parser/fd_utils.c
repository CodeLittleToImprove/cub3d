#include "../../includes/parser.h"

int	open_input_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	open_output_file(const char *outputfilename)
{
	int	fd;

	fd = open(outputfilename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error creating output file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

bool	handle_invalid_color_line(char *line, size_t line_number, int fd, bool first_color_found)
{
	if (first_color_found && is_invalid_color_line(line))
	{
		printf("Error: Found non-color line within color definitions at line %ld: %s\n", line_number, line);
		free(line);
		close(fd);
		return (false);
	}
	return (true);
}

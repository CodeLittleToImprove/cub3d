#include "../../includes/parser.h"

int	open_input_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening input file");
		// exit(EXIT_FAILURE);
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
		// exit(EXIT_FAILURE);
	}
	return (fd);
}

int	rgb_to_hex(int rgb[3])
{
	return (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
}

void	set_rgb_hex_in_colors(t_colors *colors)
{
	colors->rgb_hex_floor = rgb_to_hex(colors->rgb_floor);
	colors->rgb_hex_ceiling = rgb_to_hex(colors->rgb_ceiling);
}
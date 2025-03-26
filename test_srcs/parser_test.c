#include "../includes/parser.h"

int	main(int argc, char *argv[])
{
	t_map		map;
	t_colors	colors;
	t_textures	textures;

	if (argc != 2)
		return (-1);

	if(detect_color(argv[1], &colors))
	{
		printf("colors extraction success\n");
		print_colors(&colors);
	}
	else
		printf("colors extraction fail \n"); // stop program

//	printf("map->end_line %ld\n", map.map_end_line);
	if (detect_textures(argv[1], &textures))
	{
		printf("Textures extracted successfully:\n");
		print_textures(&textures);
	}
	else
	{
		printf("Failed to extract all textures.\n");
	}
	if (extract_map(argv[1], &map))
	{
		printf("map extraction success\n");
	}
	else
	{
		printf("map extraction fail \n");
	}
	// read_map_file(argv[1], &map); // reads the original file
	read_map_file("temp_map.cub", &map); // reads the temp file for testing
}
#include "../../includes/parser.h"
#include "../../includes/cub3d.h"

bool	check_map_order(t_map *map, t_colors *colors,
						t_textures *textures)
{
	if (map->map_end_line < colors->color_start_line
		|| map->map_end_line < textures->last_texture_line)
	{
		printf("Error: Map ends at line %zu,"
			   "but colors start at %zu and textures end at %zu\n",
			   map->map_end_line, colors->color_start_line,
			   textures->last_texture_line);
		return (false);
	}
	return (true);
}


// change detect textures to exit when its detected multiple textures to exit properly
// write a check if map is not last cancel everything
int	main(int argc, char *argv[])
{
	t_map		map;
	t_colors	colors;
	t_textures	textures;

	if (argc != 2)
		return (1);
	set_parser_default_values(&map, &textures);
	if (!detect_color(argv[1], &colors))
		return (handle_error("Error: Failed to extract colors.", &map, &textures, 2));
	printf("Colors extracted successfully.\n"); //DEBUG
	print_colors(&colors); //DEBUG

	if (!detect_textures(argv[1], &textures))
		return (handle_error("Error: Failed to extract textures.", &map, &textures, 3));
	printf("Textures extracted successfully.\n"); //DEBUG
	print_textures(&textures); //DEBUG

	if (!extract_map(argv[1], &map))
		return (handle_error("Error: Failed to extract map.", &map, &textures, 4));
	printf("Map extracted successfully.\n"); //DEBUG

//	if (!check_map_order(&map, &colors, &textures)) // not needed because it already works without it
//		return (handle_error("Error: Map not last.", &map, &textures, 5));

	if (!read_map_file("temp_map.cub", &map))
		return (handle_error("Error: Failed to read temp map file.", &map, &textures, 5));
	printf("Successfully read map file.\n"); //DEBUG
//	printf("Map parsing successful.\n"); // DEBUG
//	print_grid(map.grid);
	parser_cleanup(&map, &textures);
}

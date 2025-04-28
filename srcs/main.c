#include "../includes/parser.h"
#include "../includes/cub3d.h"

int	close_mlx(t_data *data)
{
	int i;

	mlx_destroy_image(data->mlx, data->image.img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	i = 0;
	while (i < 4)
	{
		free(data->textures[i]);
		i++;
	}
	if (data->map)
	{
		free_grid(data->map);
		data->map = NULL; // Prevent future invalid access
	}
	free(data->textures);
	exit (0);
}

int	main(int argc, char *argv[])
{
	t_map		map;
	t_colors	colors;
	t_textures	textures;
	t_data	data;

	if (argc != 2)
		return (-1);
	set_parser_default_values(&map, &textures);
	if (!detect_color(argv[1], &colors))
		return handle_error("Error: Failed to extract colors.", &map, &textures, 2);
	printf("Colors extracted successfully.\n"); //DEBUG
	print_colors(&colors); //DEBUG

	if (!detect_textures(argv[1], &textures))
		return handle_error("Error: Failed to extract textures.", &map, &textures, 3);
	printf("Textures extracted successfully.\n"); //DEBUG
	print_textures(&textures); //DEBUG

	if (!extract_map(argv[1], &map))
		return handle_error("Error: Failed to extract map.", &map, &textures, 4);
	printf("Map extracted successfully.\n"); //DEBUG

	if (!read_map_file("temp_map.cub", &map))
		return handle_error("Error: Failed to read temp map file.", &map, &textures, 5);
	printf("Successfully read map file.\n"); //DEBUG
//	printf("Map parsing successful.\n"); // DEBUG
//	print_grid(map.grid);

	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	init_data(&data, &map, &colors, &textures);
	mlx_hook(data.win, 17, 1L << 17, close_mlx, &data);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	parser_cleanup(&map, &textures);
}
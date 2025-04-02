#include "../includes/parser.h"
#include "../includes/cub3d.h"

int	close_mlx(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	exit(0);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_map		map;
	t_colors	colors;
	t_textures	textures;
	t_data	data;
	t_image	img;


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
	// print_grid(map.grid);
	// printf("player x pos = %ld\n", map.player_x);
	// printf("player y pos = %ld\n", map.player_y);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "3D GAME!");
	img.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	data_init(&data, &map, &img);
	mlx_hook(data.win, 17, 1L << 17, close_mlx, &data);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	free_grid(map.grid);
	free_textures(&textures);
}
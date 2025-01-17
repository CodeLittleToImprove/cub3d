
#include "../includes/cub.h"

char **get_map();

void draw_map(t_game *pGame);

void put_pixel(int x, int y, int color, t_game *game)
{
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;

	int index = y * game->size_line + x * game->bpp / 8;
	// Write the blue component of the color (lowest 8 bits of color) to the buffer.
	game->data[index] = color & 0xFF;

	// Write the green component of the color (bits 8–15 of color) to the buffer.
	game->data[index + 1] = (color >> 8) & 0xFF;

	// Write the red component of the color (bits 16–23 of color) to the buffer.
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void clear_image(t_game *game)
{
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			put_pixel(x, y, 0, game);
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x, y + i, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, game);
	for (int i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, game);
}

void init_game(t_game *game)
{
	init_player(&game->player);
	game->map = get_map();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "GAME");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

char	**get_map(void)
{
	char	**map = malloc(sizeof(char *) * 11);
	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100000000000001";
	map[3] = "100000000000001";
	map[4] = "100000000000001";
	map[5] = "100000000000001";
	map[6] = "100000000000001";
	map[7] = "100000000000001";
	map[8] = "100000000000001";
	map[9] = "111111111111111";
	map[10] = NULL;
	return (map);
}

void draw_map(t_game *game)
{
	char	**map = game->map;
	int		color = 0x0000FF;

	for(int y = 0; map[y]; y++)
		for(int x = 0; map[y][x]; x++)
			if(map[y][x] == '1')
				draw_square(x * 64 , y * 64, 64, color, game);
}

int draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(player);
	clear_image(game);
	draw_square(player->x, player->y, 64, LIME, game);
	draw_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}



int main(void)
{
	t_game game;

	init_game(&game);
	mlx_hook(game.win, KEYPRESS_EVENTS, EVENT_MASK_KEYPRESS, key_press, &game.player);
	mlx_hook(game.win, KEYRELEASE_EVENTS, EVENT_MASK_KEYRELEASE, key_release, &game.player);
	// draw_square(WIDTH / 2, HEIGHT / 2, 10, LIME, &game);
	// Close hook for clicking the X button
	mlx_hook(game.win, CLOSE_X_BUTTON, 0, close_program, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);

	mlx_loop(game.mlx);

	return 0;

}

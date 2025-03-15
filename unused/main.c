
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

char	**get_map(void) // map seems to scale with resolution, you have to add more numbers to map otherwise its gonna crash
{
	char	**map = malloc(sizeof(char *) * 11);
	// map[0] = "111111111111111";
	// map[1] = "100000000000001";
	// map[2] = "100000000000001";
	// map[3] = "100000000000001";
	// map[4] = "100000000000001";
	// map[5] = "100000000000001";
	// map[6] = "100000000000001";
	// map[7] = "100000000000001";
	// map[8] = "100000000000001";
	// map[9] = "111111111111111";
	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100000000000001";
	map[3] = "100001000000001";
	map[4] = "100000010000001";
	map[5] = "100000001000001";
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
	int		color = BLUE;

	for(int y = 0; map[y]; y++)
		for(int x = 0; map[y][x]; x++)
			if(map[y][x] == '1')
				draw_square(x * BLOCKSIZE , y * BLOCKSIZE, BLOCKSIZE, color, game); // x spacing between squares, y spacing between squares, size of square
}

float distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - game->player.angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle);
	return fix_dist;
}

bool	touch(float px, float py, t_game *game)
{
	int x = px / BLOCKSIZE;
	int y = py / BLOCKSIZE;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

void draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->x;
	float ray_y = player->y;

	while(!touch(ray_x, ray_y, game))
	{
		if(DEBUG)
			put_pixel(ray_x, ray_y, RED, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if(!DEBUG)
	{
		float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
		float height = (BLOCKSIZE / dist) * (WIDTH / 2);
		int start_y = (HEIGHT - height) / 2;
		int end = start_y + height;
		while(start_y < end)
		{
			put_pixel(i, start_y, 255, game);
			start_y++;
		}
	}
}

int	draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(player);
	clear_image(game);
	if(DEBUG)
	{
		// Draw the player's position as a square
		draw_square(player->x, player->y, 10, LIME, game);
		// Draw the 2D map
		draw_map(game);
	}

	// Raycasting to render the 3D view
	float fraction = PI / 3 / WIDTH;       // Fractional angle between rays
	float start_x = player->angle - PI / 6; // Start ray angle (FOV center - half FOV)
	int i = 0;                              // Pixel column index

	// Loop through all columns of the screen and cast rays
	while (i < WIDTH)
	{
		// Cast a single ray and draw it
		draw_line(player, game, start_x, i);

		// Increment the ray angle by the fractional angle
		start_x += fraction;

		// Move to the next column
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}

int main(void)
{
	t_game game;

	init_game(&game);
	mlx_hook(game.win, KEYPRESS_EVENTS, EVENT_MASK_KEYPRESS, key_press, &game.player);
	mlx_hook(game.win, KEYRELEASE_EVENTS, EVENT_MASK_KEYRELEASE, key_release, &game.player);
	// Close hook for clicking the X button
	mlx_hook(game.win, CLOSE_X_BUTTON, 0, close_program, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);

	mlx_loop(game.mlx);

	return 0;

}

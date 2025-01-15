
#include "../includes/cub.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
}

int	key_press(int keycode, t_player *player)
{
	if(keycode == W)
		player->key_up = true;
	if(keycode == S)
		player->key_down = true;
	if(keycode == A)
		player->key_left = true;
	if(keycode == D)
		player->key_right = true;
	return 0;
}

int	key_release(int keycode, t_player *player)
{
	if(keycode == W)
		player->key_up = false;
	if(keycode == S)
		player->key_down = false;
	if(keycode == A)
		player->key_left = false;
	if(keycode == D)
		player->key_right = false;
	return 0;
}

void	move_player(t_player *player)
{
	int	speed = 5;

	// Vertical movement (up and down)
	if (player->key_up)
		player->y -= speed;  // Move up by decreasing the y-coordinate
	if (player->key_down)
		player->y += speed;  // Move down by increasing the y-coordinate

	// Horizontal movement (left and right)
	if (player->key_left)
		player->x -= speed;  // Move left by decreasing the x-coordinate
	if (player->key_right)
		player->x += speed;  // Move right by increasing the x-coordinate
}

#include "../includes/cub.h"
#include <X11/keysym.h>

void	init_player(t_player *player)
{
	// Set initial player position at the center of the screen
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;

	// Set the initial facing direction (90 degrees or PI/2 radians)
	player->angle = PI / 2;

	// Initialize movement and rotation flags
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
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
	if(keycode == LEFT)
		player->left_rotate = true;
	if(keycode == RIGHT)
		player->right_rotate = true;
	if (keycode == XK_Escape)
		exit(0); // Exit the program cleanly
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
	if(keycode == LEFT)
		player->left_rotate = false;
	if(keycode == RIGHT)
		player->right_rotate = false;
	return 0;
}

void	move_player(t_player *player)
{
	int		speed = 3;
	float	angle_speed = 0.03;
	float	cos_angle= cos(player->angle);
	float	sin_angle= sin(player->angle);

	// Handle player rotation to the left
	if(player->left_rotate)
		player->angle -= angle_speed;

	// Handle player rotation to the right
	if(player->right_rotate)
		player->angle += angle_speed;

	// Normalize the angle to keep it within [0, 2*PI]
	if(player->angle > 2 * PI)
		player->angle = 0;
	if(player->angle < 0)
		player->angle = 2 * PI;

	// If the "up" key is pressed, move the player forward in the direction of the angle
	if (player->key_up)
	{
		player->x += cos_angle * speed;  // Move in the direction of cos(angle) along x-axis
		player->y += sin_angle * speed;  // Move in the direction of sin(angle) along y-axis
	}

	// If the "down" key is pressed, move the player backward (reverse of forward)
	if (player->key_down)
	{
		player->x -= cos_angle * speed;  // Move opposite to cos(angle) along x-axis
		player->y -= sin_angle * speed;  // Move opposite to sin(angle) along y-axis
	}

	// If the "left" key is pressed, move the player to the left relative to the direction of the angle
	if (player->key_left)
	{
		player->x += sin_angle * speed;  // Swap: Move in the direction of sin(angle) along x-axis (perpendicular)
		player->y -= cos_angle * speed;  // Swap: Move opposite to cos(angle) along y-axis (perpendicular)
	}

	// If the "right" key is pressed, move the player to the right relative to the direction of the angle
	if (player->key_right)
	{
		player->x -= sin_angle * speed;  // Swap: Move opposite to sin(angle) along x-axis (perpendicular)
		player->y += cos_angle * speed;  // Swap: Move in the direction of cos(angle) along y-axis (perpendicular)
	}
}

int close_program(t_game *game)
{
	// Clean up resources here if needed (e.g., free memory, destroy images)
	exit(0); // Exit the program
	return 0;
}
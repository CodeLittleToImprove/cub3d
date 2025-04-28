/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:10:55 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/28 17:41:17 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_mlx(data);
	if (keycode == 115)
		data->key.s = 1;
	if (keycode == 97)
		data->key.a = 1;
	if (keycode == 119)
		data->key.w = 1;
	if (keycode == 100)
		data->key.d = 1;
	if (keycode == 65361)
		data->key.left = 1;
	if (keycode == 65363)
		data->key.right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 115)
		data->key.s = 0;
	if (keycode == 97)
		data->key.a = 0;
	if (keycode == 119)
		data->key.w = 0;
	if (keycode == 100)
		data->key.d = 0;
	if (keycode == 65361)
		data->key.left = 0;
	if (keycode == 65363)
		data->key.right = 0;
	return (0);
}

void	move(t_dir dir, t_data *data, double player_d1, double player_d2)
{
	if (dir == SOUTH || dir == EAST)
		player_d1 = (-1 * player_d1);
	if (dir == SOUTH || dir == WEST)
		player_d2 = (-1 * player_d2);
	if (!has_collision(data, player_d1, 1))
		data->player.x += player_d1;
	if (!has_collision(data, player_d2, 0))
		data->player.y += player_d2;
}

void	move_player(t_data *data)
{
	data->player.dx = cos(data->player.a) * SPEED;
	data->player.dy = sin(data->player.a) * SPEED;
	if (data->key.left)
		data->player.a -= CAM_SPEED;
	if (data->key.right)
		data->player.a += CAM_SPEED;
	data->player.a = get_angle(data->player.a);
	if (data->key.s)
		move(SOUTH, data, data->player.dx, data->player.dy);
	if (data->key.a)
		move(WEST, data, data->player.dy, data->player.dx);
	if (data->key.w)
		move(NORTH, data, data->player.dx, data->player.dy);
	if (data->key.d)
		move(EAST, data, data->player.dy, data->player.dx);
}

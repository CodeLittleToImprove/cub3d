/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:10:55 by pschmunk          #+#    #+#             */
/*   Updated: 2025/03/15 15:32:38 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_mlx(data);
	if (keycode == 115)
		data->key_W = 1;
	if (keycode == 97)
		data->key_A = 1;
	if (keycode == 119)
		data->key_S = 1;
	if (keycode == 100)
		data->key_D = 1;
	if (keycode == 65361)
		data->key_left = 1;
	if (keycode == 65363)
		data->key_right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 115)
		data->key_W = 0;
	if (keycode == 97)
		data->key_A = 0;
	if (keycode == 119)
		data->key_S = 0;
	if (keycode == 100)
		data->key_D = 0;
	if (keycode == 65361)
		data->key_left = 0;
	if (keycode == 65363)
		data->key_right = 0;
	return (0);
}

void	move_player(t_data *data)
{
	data->playerDX = cos(data->playerA) * SPEED;
	data->playerDY = sin(data->playerA) * SPEED;
	if (data->key_left)
		data->playerA -= CAM_SPEED;
	if (data->key_right)
		data->playerA += CAM_SPEED;
	data->playerA = get_angle(data->playerA);
	if (data->key_W)
	{
		data->playerX -= data->playerDX;
		data->playerY -= data->playerDY;
	}
	if (data->key_A)
	{
		data->playerX += data->playerDY;
		data->playerY -= data->playerDX;
	}
	if (data->key_S)
	{
		data->playerX += data->playerDX;
		data->playerY += data->playerDY;
	}
	if (data->key_D)
	{
		data->playerX -= data->playerDY;
		data->playerY += data->playerDX;
	}
}
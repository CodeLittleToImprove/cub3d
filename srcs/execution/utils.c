/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:19 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/22 19:50:29 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	get_angle(double angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	get_spawn_angle(t_data *data, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->tiles_y)
	{
		x = 0;
		while (x < data->tiles_x)
		{
			if (data->map[y][x] == 'S')
				player->a = PI / 2;
			else if (data->map[y][x] == 'N')
				player->a = 3 * PI / 2;
			else if (data->map[y][x] == 'W')
				player->a = PI;
			else if (data->map[y][x] == 'E')
				player->a = 2 * PI;
			x++;
		}
		y++;
	}
}

int	to_grid_size(int num)
{
	if (num <= TILE)
		return (0);
	return (num / TILE);
}

int	has_collision(t_data *data, t_dir *dir, double player_d, int is_x)
{
	int	y;
	int	x;

	if (is_x)
	{
		y = to_grid_size((int)data->player.y);
		x = to_grid_size((int)(data->player.x + (player_d * 8)));
	}
	else
	{
		x = to_grid_size((int)data->player.x);
		y = to_grid_size((int)(data->player.y + (player_d * 8)));
	}
	if (data->map[y][x] == '1')
		return (1);
	return (0);
}

void	px_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= data->width || y >= data->height)
		return ;
	dst = data->image.addr
		+ (y * data->image.line_length + x * (data->image.bpp / 8));
	*(unsigned int *)dst = color;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:13:09 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/15 19:18:33 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_line(t_data *data, int x0, int y0, int x1, int y1)
{
	int	dist_x;
	int	dist_y;
	int	step_x;
	int	step_y;
	int	error;
	int	error2;

	dist_x = abs(x1 - x0);
	dist_y = abs(y1 - y0);
	if (x0 < x1)
		step_x = 1;
	else
		step_x = -1;
	if (y0 < y1)
		step_y = 1;
	else
		step_y = -1;
	error = dist_x - dist_y;
	error2 = 0;
	while(1)
	{
		px_put(data->image, x0, y0, 0xFF0000);
		if (x0 == x1 && y0 == y1)
			break;
		error2 = error * 2;
		if (error2 > -dist_y)
		{
			error -= dist_y;
			x0 += step_x;
		}
		if (error2 < dist_x)
		{
			error += dist_x;
			y0 += step_y;
		}
	}
}

void	render_small_square(t_image *img, int x, int y, int color)
{
	size_t	i_end = x + 32;
	size_t	j_end = y + 32;

	for (size_t i = x; i < i_end; i++)
	{
		for (size_t j = y; j < j_end; j++)
		{
			px_put(img, i, j, color);
		}
	}
}

void	render_square(t_image *img, int x, int y, int color)
{
	size_t	i_start = x * TILE;
	size_t	i_end = (x + 1) * TILE;
	size_t	j_start = y * TILE;
	size_t	j_end = (y + 1) * TILE;

	for (size_t i = i_start; i < i_end; i++)
	{
		for (size_t j = j_start; j < j_end; j++)
			px_put(img, i, j, color);
	}
}

void	render_map(t_data *data)
{
	for (size_t y = 0; y < TILES_Y; y++)
	{
		for (size_t x = 0; x < TILES_X; x++)
		{
			if (data->map[y][x] == '1')
				render_square(data->image, x, y, 0xFFFFFF);
			else
				render_square(data->image, x, y, 0x000000);
		}
	}
}

void	render_player(t_data *data)
{
	int	y;

	y = 0;
	for (size_t x = 0; x < data->width; x++)
	{
		for (size_t y = 0; y < data->height; y++)
		{
			if (x == (size_t)data->player->x && y == (size_t)data->player->y)
				render_small_square(data->image, x, y, 0x0000FF);
		}
	}
}
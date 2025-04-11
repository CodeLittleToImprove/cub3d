/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:13:51 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/11 15:06:53 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_line(t_data *data, int x0, int y0, int x1, int y1, int color)
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
		px_put(data->image, x0, y0, color);
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
			px_put(img, i, j, color);
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
	for (size_t x = 0; x < WIDTH; x++)
	{
		for (size_t y = 0; y < HEIGHT; y++)
		{
			if (x == (size_t)data->playerX && y == (size_t)data->playerY)
				render_small_square(data->image, x, y, 0x0000FF);
		}
	}
}

void	clear_image(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < HEIGHT / 2)
				px_put(data->image, x, y, 0x366FDF);
			else
				px_put(data->image, x, y, 0x6F921C);
			y++;
		}
		x++;
	}
}

int	render(t_data *data)
{
	clear_image(data);
	render_map(data);
	move_player(data);
	draw_rays(data);
	render_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
	return (0);
}
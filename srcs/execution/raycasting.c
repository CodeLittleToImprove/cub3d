/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:37:42 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/11 15:51:08 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	calc_dist(t_data *data, double x0, double y0, double x1, double y1)
{
	double	delta_x;
	double	delta_y;
	double	angle;

	delta_x = x1 - x0;
	delta_y = y1 - y0;
	angle = atan2(delta_y, delta_x) - data->playerA;
	angle = get_angle2(angle);
	return ((sqrt(delta_x * delta_x + delta_y * delta_y)) * cos(angle));
}

int	is_in_bound(t_data *data)
{
	if (data->mapX >= 0 && data->mapY >= 0
		&& data->mapX < TILES_X && data->mapY < TILES_Y)
		return (1);
	return (0);
}

double	get_dist(t_data *data, int end, double *x, double *y)
{
	int	i;

	i = 0;
	while (i < end)
	{
		data->mapX = (int)data->rayX / TILE;
		data->mapY = (int)data->rayY / TILE;
		if (is_in_bound(data) && data->map[data->mapY][data->mapX] == '1')
		{
			*x = data->rayX;
			*y = data->rayY;
			return (calc_dist(data, data->playerX, data->playerY, *x, *y));
		}
		else
		{
			data->rayX += data->offsetX;
			data->rayY += data->offsetY;
			i++;
		}
	}
	return (1000000);
}

int	set_horizontal(t_data *data, double tan)
{
	if (data->rayA > PI)
	{
		data->rayY = ((int)data->playerY / TILE) * TILE - 0.0001;
		data->rayX = ((int)data->playerY - data->rayY)
			* tan + (int)data->playerX;
		data->offsetY = -TILE;
		data->offsetX = TILE * tan;
		return (1);
	}
	if (data->rayA < PI)
	{
		data->rayY = ((int)data->playerY / TILE) * TILE + TILE;
		data->rayX = ((int)data->playerY - data->rayY)
			* tan + (int)data->playerX;
		data->offsetY = TILE;
		data->offsetX = -TILE * tan;
	}
	return (0);
}

int	set_vertical(t_data *data, double tan)
{
	if (data->rayA > (PI / 2) && data->rayA < ((3 * PI) / 2))
	{
		data->rayX = ((int)data->playerX / TILE) * TILE - 0.0001;
		data->rayY = ((int)data->playerX - data->rayX)
			* tan + (int)data->playerY;
		data->offsetX = -TILE;
		data->offsetY = TILE * tan;
		return (1);
	}
	if (data->rayA < (PI / 2) || data->rayA > ((3 * PI) / 2))
	{
		data->rayX = ((int)data->playerX / TILE) * TILE + TILE;
		data->rayY = ((int)data->playerX - data->rayX)
			* tan + (int)data->playerY;
		data->offsetX = TILE;
		data->offsetY = -TILE * tan;
	}
	return (0);
}

int	draw_3d(t_data *data, int x, double dis, int is_horizontal)
{
	double	tex_x;
	double	tex_y;
	double	tex_y_step;
	double	wall_height;
	double	offset;
	int		y;
	int		tex_type;

	wall_height = (TILE * HEIGHT) / dis;
	offset = (HEIGHT / 2) - (wall_height / 2);
	tex_y_step = TILE / wall_height;
	y = 0;
	if (is_horizontal)
	{
		if (data->rayA > 0 && data->rayA < PI)
			tex_type = 2;
		else
			tex_type = 1;
		tex_x = (int)data->rayX % 64;
	}
	else
	{
		if (data->rayA > (PI / 2) && data->rayA < ((3 * PI) / 2))
			tex_type = 3;
		else
			tex_type = 0;
		tex_x = (int)data->rayY % 64;
	}
	tex_y = 0;
	while (y < wall_height)
	{
		px_put(data->image, x, offset + y, data->textures[tex_type][(int)tex_y * TILE + (int)tex_x]);
		y++;
		tex_y += tex_y_step;
	}
	x++;
	while (x % (WIDTH / FOV) != 0)
	{
		y = 0;
		tex_y = 0;
		while (y < wall_height)
		{
			px_put(data->image, x, offset + y, data->textures[tex_type][(int)tex_y * TILE + (int)tex_x]);
			y++;
			tex_y += tex_y_step;
		}
		x++;
	}
	return (x);
}

void	draw_rays(t_data *data)
{
	int		x;
	int		i;
	int 	color;
	int		is_horizontal;
	double	dis_h;
	double	dis_v;
	double	dis;

	data->rayA = get_angle(data->playerA - (DEGREE * (FOV / 2)));
	i = 0;
	x = 0;
	while (i < FOV)
	{
		data->horizontalX = data->playerX;
		data->horizontalY = data->playerY;
		set_horizontal(data, -1 / tan(data->rayA));
		dis_h = get_dist(data, TILES_Y, &data->horizontalX, &data->horizontalY);
		data->verticalX = data->playerX;
		data->verticalY = data->playerY;
		set_vertical(data, -tan(data->rayA));
		dis_v = get_dist(data, TILES_X, &data->verticalX, &data->verticalY);
		if (dis_v < dis_h)
		{
			data->rayX = data->verticalX;
			data->rayY = data->verticalY;
			dis = dis_v;
			is_horizontal = 0;
			color = 0x73504A;
		}
		else if (dis_h < dis_v)
		{
			data->rayX = data->horizontalX;
			data->rayY = data->horizontalY;
			dis = dis_h;
			is_horizontal = 1;
			color = 0x44393C;
		}
		// render_line(data, (int)data->playerX, (int)data->playerY,
		// 	(int)data->rayX, (int)data->rayY, color);
		x = draw_3d(data, x, dis, is_horizontal);
		data->rayA = data->rayA + DEGREE;
		data->rayA = get_angle(data->rayA);
		i++;
	}
}

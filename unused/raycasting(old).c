/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:37:42 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/16 23:57:25 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	dist(t_data *data, double delta_x, double delta_y)
{
	double	angle;

	angle = atan2(delta_y, delta_x) - data->player.a;
	angle = get_angle(angle);
	return ((sqrt(delta_x * delta_x + delta_y * delta_y)) * cos(angle));
}

int	is_in_bound(t_data *data, int x, int y)
{
	if (x >= 0 && y >= 0
		&& x < TILES_X && y < TILES_Y)
		return (1);
	return (0);
}

double	get_dist(t_data *data, int end, double *x, double *y)
{
	int	i;
	int	map_x;
	int	map_y;

	i = 0;
	while (i < end)
	{
		map_x = (int)data->ray.x / TILE;
		map_y = (int)data->ray.y / TILE;
		if (is_in_bound(data, map_x, map_y) && data->map[map_y][map_x] == '1')
		{
			*x = data->ray.x;
			*y = data->ray.y;
			return (dist(data, *x - data->player.x, *y - data->player.y));
		}
		else
		{
			data->ray.x += data->ray.off_x;
			data->ray.y += data->ray.off_y;
			i++;
		}
	}
	return (1000000);
}

double	set_horizontal(t_data *data, double tan)
{

	if (data->ray.a > PI)
	{
		data->ray.y = ((int)data->player.y / TILE) * TILE - 0.0001;
		data->ray.x = ((int)data->player.y - data->ray.y)
			* tan + (int)data->player.x;
		data->ray.off_y = -TILE;
		data->ray.off_x = TILE * tan;
		return (1);
	}
	if (data->ray.a < PI)
	{
		data->ray.y = ((int)data->player.y / TILE) * TILE + TILE;
		data->ray.x = ((int)data->player.y - data->ray.y)
			* tan + (int)data->player.x;
		data->ray.off_y = TILE;
		data->ray.off_x = -TILE * tan;
	}
	return (0);
}

int	set_vertical(t_data *data, double tan)
{
	if (data->ray.a > (PI / 2) && data->ray.a < ((3 * PI) / 2))
	{
		data->ray.x = ((int)data->player.x / TILE) * TILE - 0.0001;
		data->ray.y = ((int)data->player.x - data->ray.x)
			* tan + (int)data->player.y;
		data->ray.off_x = -TILE;
		data->ray.off_y = TILE * tan;
		return (1);
	}
	if (data->ray.a < (PI / 2) || data->ray.a > ((3 * PI) / 2))
	{
		data->ray.x = ((int)data->player.x / TILE) * TILE + TILE;
		data->ray.y = ((int)data->player.x - data->ray.x)
			* tan + (int)data->player.y;
		data->ray.off_x = TILE;
		data->ray.off_y = -TILE * tan;
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

	wall_height = (TILE * data->height) / dis;
	offset = (data->height / 2) - (wall_height / 2);
	tex_y_step = TILE / wall_height;
	y = 0;
	if (is_horizontal)
	{
		if (data->ray.a > 0 && data->ray.a < PI)
			tex_type = 2;
		else
			tex_type = 1;
		tex_x = (int)data->ray.x % 64;
	}
	else
	{
		if (data->ray.a > (PI / 2) && data->ray.a < ((3 * PI) / 2))
			tex_type = 3;
		else
			tex_type = 0;
		tex_x = (int)data->ray.y % 64;
	}
	tex_y = 0;
	while (y < wall_height)
	{
		px_put(data, x, offset + y, data->textures[tex_type][(int)tex_y * TILE + (int)tex_x]);
		y++;
		tex_y += tex_y_step;
	}
	x++;
	while (x % (data->width / data->fov) != 0)
	{
		y = 0;
		tex_y = 0;
		while (y < wall_height)
		{
			px_put(data, x, offset + y, data->textures[tex_type][(int)tex_y * TILE + (int)tex_x]);
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
	int		is_horizontal;
	double	dis_h;
	double	dis_v;
	double	dis;

	data->ray.a = get_angle(data->player.a - (data->degree * (data->fov / 2)));
	i = 0;
	x = 0;
	while (i < data->fov)
	{
		data->ray.hor_x = data->player.x;
		data->ray.hor_y = data->player.y;
		set_horizontal(data, -1 / tan(data->ray.a));
		dis_h = get_dist(data, TILES_Y, &data->ray.hor_x, &data->ray.hor_y);
		data->ray.ver_x = data->player.x;
		data->ray.ver_y = data->player.y;
		set_vertical(data, -tan(data->ray.a));
		dis_v = get_dist(data, TILES_X, &data->ray.ver_x, &data->ray.ver_y);
		if (dis_v < dis_h)
		{
			data->ray.x = data->ray.ver_x;
			data->ray.y = data->ray.ver_y;
			dis = dis_v;
			is_horizontal = 0;
		}
		else if (dis_h < dis_v)
		{
			data->ray.x = data->ray.hor_x;
			data->ray.y = data->ray.hor_y;
			dis = dis_h;
			is_horizontal = 1;
		}
		x = draw_3d(data, x, dis, is_horizontal);
		data->ray.a = data->ray.a + data->degree;
		data->ray.a = get_angle(data->ray.a);
		i++;
	}
}

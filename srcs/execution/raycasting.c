/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:37:42 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/29 18:15:01 by pschmunk         ###   ########.fr       */
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
		&& x < data->tiles_x
		&& y < data->tiles_y)
		return (1);
	else if (x >= 0 && y >= 0
		&& x < (int)ft_strlen(data->map[(int)data->player.y / TILE])
		&& y < data->tiles_y)
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

double	get_horizontal(t_data *data, double tan)
{
	data->ray.hor_x = data->player.x;
	data->ray.hor_y = data->player.y;
	if (data->ray.a > PI)
	{
		data->ray.y = ((int)data->player.y / TILE) * TILE - 0.0001;
		data->ray.x = ((int)data->player.y - data->ray.y)
			* tan + (int)data->player.x;
		data->ray.off_y = -TILE;
		data->ray.off_x = TILE * tan;
	}
	else
	{
		data->ray.y = ((int)data->player.y / TILE) * TILE + TILE;
		data->ray.x = ((int)data->player.y - data->ray.y)
			* tan + (int)data->player.x;
		data->ray.off_y = TILE;
		data->ray.off_x = -TILE * tan;
	}
	return (get_dist(data, data->tiles_y, &data->ray.hor_x, &data->ray.hor_y));
}

double	get_vertical(t_data *data, double tan)
{
	data->ray.ver_x = data->player.x;
	data->ray.ver_y = data->player.y;
	if (data->ray.a > (PI / 2) && data->ray.a < ((3 * PI) / 2))
	{
		data->ray.x = ((int)data->player.x / TILE) * TILE - 0.0001;
		data->ray.y = ((int)data->player.x - data->ray.x)
			* tan + (int)data->player.y;
		data->ray.off_x = -TILE;
		data->ray.off_y = TILE * tan;
	}
	else
	{
		data->ray.x = ((int)data->player.x / TILE) * TILE + TILE;
		data->ray.y = ((int)data->player.x - data->ray.x)
			* tan + (int)data->player.y;
		data->ray.off_x = TILE;
		data->ray.off_y = -TILE * tan;
	}
	return (get_dist(data, data->tiles_x, &data->ray.ver_x, &data->ray.ver_y));
}

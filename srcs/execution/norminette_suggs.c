/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette_suggs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 02:48:41 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/29 18:52:35 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	get_color(t_data *data, double tex_y, int is_horizontal)
{
	int	tex_x;
	int	tex_type;

	if (is_horizontal)
	{
		if (data->ray.a > 0 && data->ray.a < PI)
			tex_type = 2;
		else
			tex_type = 1;
		tex_x = (int)data->ray.hor_x % 64;
	}
	else
	{
		if (data->ray.a > (PI / 2) && data->ray.a < ((3 * PI) / 2))
			tex_type = 3;
		else
			tex_type = 0;
		tex_x = (int)data->ray.ver_y % 64;
	}
	return (data->textures[tex_type][(int)tex_y * TILE + tex_x]);
}

void	norminette_is_shit(t_data *data, double wall_height, int x, int is_hor)
{
	double	offset;
	double	tex_y_step;
	int		y;
	double	tex_y;

	offset = (data->height / 2) - (wall_height / 2);
	tex_y_step = TILE / wall_height;
	y = 0;
	tex_y = 0;
	while (y < wall_height)
	{
		px_put(data, x, offset + y, get_color(data, tex_y, is_hor));
		y++;
		tex_y += tex_y_step;
	}
}

int	draw_vertical_line(t_data *data, int x, double dis, int is_horizontal)
{
	double	wall_height;

	wall_height = (TILE * data->height) / dis;
	norminette_is_shit(data, wall_height, x, is_horizontal);
	x++;
	while (x % (data->width / data->fov) != 0)
	{
		norminette_is_shit(data, wall_height, x, is_horizontal);
		x++;
	}
	return (x);
}

void	draw_rays(t_data *data)
{
	int		x;
	int		i;
	double	dis_h;
	double	dis_v;

	i = 0;
	x = 0;
	data->ray.a = get_angle(data->player.a - (data->degree * (data->fov / 2)));
	while (i < data->fov)
	{
		dis_h = get_horizontal(data, -1 / tan(data->ray.a));
		dis_v = get_vertical(data, -tan(data->ray.a));
		if (dis_v < dis_h)
			x = draw_vertical_line(data, x, dis_v, 0);
		else if (dis_h < dis_v)
			x = draw_vertical_line(data, x, dis_h, 1);
		data->ray.a = get_angle(data->ray.a + data->degree);
		i++;
	}
}

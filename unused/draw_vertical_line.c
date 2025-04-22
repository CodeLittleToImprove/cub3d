/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 02:38:04 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/17 02:44:52 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	draw_vertical_line_but_much_cooler_than_norminette_can_comprehend(t_data *data, int x, double dis, int is_horizontal)
{
	double	wall_height;
	double	offset;
	double	tex_y_step;
	int		y;
	double	tex_y;

	wall_height = (TILE * data->height) / dis;
	offset = (data->height / 2) - (wall_height / 2);
	tex_y_step = TILE / wall_height;
	do
	{
		y = 0;
		tex_y = 0;
		while (y < wall_height)
		{
			px_put(data, x, offset + y, get_color(data, tex_y, is_horizontal));
			y++;
			tex_y += tex_y_step;
		}
		x++;
	}
	while (x % (data->width / data->fov) != 0);
	return (x);
}
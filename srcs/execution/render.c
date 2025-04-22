/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:13:51 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/16 23:53:25 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	clear_image(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->width)
	{
		y = 0;
		while (y < data->height)
		{
			if (y < data->height / 2)
				px_put(data, x, y, 0x366FDF);
			else
				px_put(data, x, y, 0x6F921C);
			y++;
		}
		x++;
	}
}

int	render(t_data *data)
{
	clear_image(data);
	move_player(data);
	draw_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	return (0);
}

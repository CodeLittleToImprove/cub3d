/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:07:26 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/07 17:57:11 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_texture(t_data *data, int i, int width, int height)
{
	t_image img;
	char	*px_data;
	int		x;
	int		y;

	if (i == 0)
		img.img = mlx_xpm_file_to_image(data->mlx, "./textures/wall_EA.xpm", &width, &height);
	else if (i == 1)
		img.img = mlx_xpm_file_to_image(data->mlx, "./textures/wall_NO.xpm", &width, &height);
	else if (i == 2)
		img.img = mlx_xpm_file_to_image(data->mlx, "./textures/wall_SO.xpm", &width, &height);
	else
		img.img = mlx_xpm_file_to_image(data->mlx, "./textures/wall_WE.xpm", &width, &height);
	if (!img.img)
		exit(1);
	px_data = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	data->textures[i] = (int *)malloc(TILE * TILE * sizeof(int));
	if (!data->textures[i])
		exit(1);
	y = 0;
	while (y < TILE)
	{
		x = 0;
		while (x < TILE)
		{
			data->textures[i][y * TILE + x] = *(int *)(px_data + (y * img.line_length) + (x * (img.bpp / 8)));
			x++;
		}
		y++;
	}
	free(img.img);
}

void	init_textures(t_data *data)
{
	int	i;

	i = 0;
	data->textures = (int **)malloc(4 * sizeof(int *));
	if (!data->textures)
		exit(1);
	while (i < 4)
	{
		init_texture(data, i, TILE, TILE);
		i++;
	}
}
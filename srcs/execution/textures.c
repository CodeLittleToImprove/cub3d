/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:07:26 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/29 16:53:15 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	select_texture(t_data *data, t_image *img, int i, t_textures *textures)
{
	int	width;
	int	height;

	width = TILE;
	height = TILE;
	if (i == 0)
		img->img = mlx_xpm_file_to_image(data->mlx,
				textures->ea_texture, &width, &height);
	else if (i == 1)
		img->img = mlx_xpm_file_to_image(data->mlx,
				textures->no_texture, &width, &height);
	else if (i == 2)
		img->img = mlx_xpm_file_to_image(data->mlx,
				textures->so_texture, &width, &height);
	else
		img->img = mlx_xpm_file_to_image(data->mlx,
				textures->we_texture, &width, &height);
	if (!img->img)
		exit(1);
}

void	init_texture(t_data *data, int i, t_textures *textures)
{
	t_image	img;
	char	*px_data;
	int		x;
	int		y;

	select_texture(data, &img, i, textures);
	px_data = mlx_get_data_addr(img.img, &img.bpp,
			&img.line_length, &img.endian);
	data->textures[i] = (int *)malloc(TILE * TILE * sizeof(int));
	if (!data->textures[i])
		exit(1);
	y = 0;
	while (y < TILE)
	{
		x = 0;
		while (x < TILE)
		{
			data->textures[i][y * TILE + x] = *(int *)
				(px_data + (y * img.line_length) + (x * (img.bpp / 8)));
			x++;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, img.img);
}

void	init_textures(t_data *data, t_textures *textures)
{
	int	i;

	i = 0;
	data->textures = (int **)malloc(4 * sizeof(int *));
	if (!data->textures)
		exit(1);
	while (i < 4)
	{
		init_texture(data, i, textures);
		i++;
	}
	free_textures(textures);
}

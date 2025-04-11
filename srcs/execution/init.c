/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:17:01 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/11 17:38:01 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	map_init(t_data *data)
{
	char *pattern[TILES_Y] = {
		"111111111111111",
		"100000000000001",
        "100000000000001",
        "100000000000001",
        "100000001100001",
        "100000000000001",
        "101110000000001",
        "1000000P0000001",
        "100000000000001",
        "100000000000001",
        "100000000001111",
        "100000000000001",
        "100000000000001",
        "100000100000001",
        "111111111111111"
    };
	for (size_t i = 0; i < TILES_X; i++)
	{
		for (size_t j = 0; j < TILES_Y; j++)
		{
			data->map[i][j] = pattern[i][j];
			if (pattern[i][j] == 'P')
			{
				data->playerX = (double)i * TILE;
				data->playerY = (double)j * TILE;
			}
		}
	}
}

void	check_spawn_angle(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < TILES_Y)
	{
		x = 0;
		while(x < TILES_X)
		{
			if (data->map[y][x] == 'S')
				data->playerA = PI / 2;
			else if (data->map[y][x] == 'N')
				data->playerA = 3 * PI / 2;
			else if (data->map[y][x] == 'W')
				data->playerA = PI;
			else if (data->map[y][x] == 'E')
				data->map[y][x] = 2 * PI;
			x++;
		}
		y++;
	}
}

void	data_init(t_data *data, t_map *map, t_image *img)
{
	// map_init(data);
	data->map = map->grid;
	// print_grid(data->map);
	data->key_W = 0;
	data->key_A = 0;
	data->key_S = 0;
	data->key_D = 0;
	data->key_left = 0;
	data->key_right = 0;
	data->playerX = map->player_x * TILE;
	data->playerY = map->player_y * TILE;
	printf("player x pos = %ff\n", data->playerX);
	printf("player y pos = %ff\n", data->playerY);
	data->playerA = 0;
	check_spawn_angle(data);
	data->playerDX = 0;
	data->playerDY = 0;
	data->rayX = 0;
	data->rayY = 0;
	data->horizontalX = 0;
	data->horizontalY = 0;
	data->verticalX = 0;
	data->verticalY = 0;
	data->dirX = -1;
	data->dirY = 0;
	data->camX = 0;
	data->camY = 0.66;
	data->image = img;
	init_textures(data);
}
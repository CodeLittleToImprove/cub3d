/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:17:01 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/28 17:34:48 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_image	init_image(t_data *data)
{
	t_image	img;

	img.img = mlx_new_image(data->mlx, data->width, data->height);
	img.addr = mlx_get_data_addr(img.img,
			&img.bpp,
			&img.line_length,
			&img.endian);
	return (img);
}

t_player	init_player(t_data *data, t_map *map)
{
	t_player	player;

	player.x = map->player_x * TILE;
	player.y = map->player_y * TILE;
	player.dx = 0;
	player.dy = 0;
	get_spawn_angle(data, &player);
	return (player);
}

t_keyinput	init_keyinputs()
{
	t_keyinput	key;

	key.w = 0;
	key.a = 0;
	key.s = 0;
	key.d = 0;
	key.left = 0;
	key.right = 0;
	return (key);
}

t_ray	init_ray()
{
	t_ray	ray;

	ray.x = 0;
	ray.y = 0;
	ray.a = 0;
	ray.hor_x = 0;
	ray.hor_y = 0;
	ray.ver_x = 0;
	ray.ver_y = 0;
	ray.off_x = 0;
	ray.off_y = 0;
	return (ray);
}

void	init_data(t_data *data, t_map *map, t_colors *colors)
{
	data->map = map->grid;
	data->degree = DEGREE / (WIN_SCALE * RES_SCALE);
	data->fov = FOV * (WIN_SCALE * RES_SCALE);
	data->width = data->fov * (3 / RES_SCALE);
	data->height = (data->width * ASPECT_Y) / ASPECT_X;
	data->tiles_x = map->max_width;
	data->tiles_y = map->max_height;
	data->floor = colors->rgb_hex_floor;
	data->ceiling = colors->rgb_hex_ceiling;
	data->win = mlx_new_window(data->mlx, data->width, data->height,
			"3D GAME!");
	data->image = init_image(data);
	data->player = init_player(data, map);
	data->key = init_keyinputs();
	data->ray = init_ray();
	init_textures(data);
}

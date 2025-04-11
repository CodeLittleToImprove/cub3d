#include "../../includes/parser.h"

void	set_default_values_color(t_colors *colors)
{
	colors->rgb_floor[0] = 0;
	colors->rgb_floor[1] = 0;
	colors->rgb_floor[2] = 0;
	colors->rgb_ceiling[0] = 0;
	colors->rgb_ceiling[1] = 0;
	colors->rgb_ceiling[2] = 0;
	colors->color_start_line = 0;
	colors->has_floor = false;
	colors->has_ceiling = false;
	colors->first_color_found = false;
	colors->found_both_colors = false;
}

void	set_default_values_map(t_map *map)
{
	map->grid = NULL;
	map->max_height = 0;
	map->max_width = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = '\0';
	map->map_end_line = 0;
}

void	set_default_values_textures(t_textures *textures)
{
	textures->no_texture = NULL;
	textures->so_texture = NULL;
	textures->we_texture = NULL;
	textures->ea_texture = NULL;
	textures->no_set = false;
	textures->so_set = false;
	textures->we_set = false;
	textures->ea_set = false;
	textures->last_texture_line = 0;
}

void	set_parser_default_values(t_map *map, t_textures *textures)
{
	set_default_values_map(map);
	set_default_values_textures(textures);
}

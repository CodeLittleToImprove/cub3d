#include "../../includes/parser.h"

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

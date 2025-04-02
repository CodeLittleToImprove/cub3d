#include "../../includes/parser.h"

void	free_grid(char **grid)
{
	size_t	row = 0;

	row = 0;
	if (!grid)
		return;
	while (grid[row])
	{
		free(grid[row]);
		row++;
	}
	free(grid);
}

void	free_textures(t_textures *textures)
{
	if (textures->no_texture)
		free(textures->no_texture);
	if (textures->so_texture)
		free(textures->so_texture);
	if (textures->we_texture)
		free(textures->we_texture);
	if (textures->ea_texture)
		free(textures->ea_texture);

	textures->no_texture = NULL;
	textures->so_texture = NULL;
	textures->we_texture = NULL;
	textures->ea_texture = NULL;
}
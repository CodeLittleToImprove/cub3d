/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:04:25 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/28 17:57:15 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TILE 64
# define WIN_SCALE 7
# define RES_SCALE 1
# define ASPECT_X 4
# define ASPECT_Y 3
# define FOV 73
# define DEGREE 0.0174533
# define PI 3.14159265359
# define SPEED 4
# define CAM_SPEED 0.05

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include "../lib/minilibx/mlx.h"
# include "../lib/libft/libft.h"
# include "../lib/libft/gnl/get_next_line_bonus.h"
# include  "parser.h"

typedef enum e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_dir;

typedef enum e_align
{
	HORIZONTAL,
	VERTICAL
}	t_align;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_player
{
	double	x;
	double	y;
	double	a;
	double	dx;
	double	dy;
}	t_player;

typedef struct s_keyinput
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keyinput;

typedef struct s_ray
{
	double	x;
	double	y;
	double	a;
	double	hor_x;
	double	hor_y;
	double	ver_x;
	double	ver_y;
	double	off_x;
	double	off_y;
}	t_ray;

typedef	struct s_data
{
	void		*mlx;
	void		*win;
	char		**map;
	int			**textures;
	int			width;
	int			height;
	int			tiles_x;
	int			tiles_y;
	int			floor;
	int			ceiling;
	int			fov;
	double		degree;
	t_image		image;
	t_player	player;
	t_keyinput	key;
	t_ray		ray;
}	t_data;

void	init_data(t_data *data, t_map *map, t_colors *colors, t_textures *textures);
void	init_textures(t_data *data, t_textures *textures);
int		close_mlx(t_data *data);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
void	move_player(t_data *data);
void	draw_rays(t_data *data);
int		render(t_data *data);
double	get_angle(double angle);
void	get_spawn_angle(t_data *data, t_player *player);
int		to_grid_size(int num);
int		has_collision(t_data *data, double player_d, int is_x);
void	px_put(t_data *data, int x, int y, int color);
double	get_horizontal(t_data *data, double tan);
double	get_vertical(t_data *data, double tan);

#endif
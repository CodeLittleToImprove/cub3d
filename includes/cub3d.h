/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pschmunk <pschmunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:04:25 by pschmunk          #+#    #+#             */
/*   Updated: 2025/04/11 21:03:18 by pschmunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TILE 64
# define TILES_X 15
# define TILES_Y 15
# define RES 7
# define FOV (73 * RES)
# define WIDTH FOV * 3
# define HEIGHT (WIDTH * 3) / 4
# define SPEED 4
# define CAM_SPEED 0.05
# define DEGREE (0.0174533 / RES)
# define PI 3.14159265359

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

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef	struct s_data
{
	void		*mlx;
	void		*win;
	char		**map;
	double		playerX;
	double		playerY;
	double		playerA;
	double		playerDX;
	double		playerDY;
	double		rayA;
	double		rayX;
	double		rayY;
	double		horizontalX;
	double		horizontalY;
	double		verticalX;
	double		verticalY;
	double		offsetX;
	double		offsetY;
	long long	mapX;
	long long	mapY;
	int			key_W;
	int			key_A;
	int			key_S;
	int			key_D;
	int			key_left;
	int			key_right;
	double		dirX;
	double		dirY;
	double		camX;
	double		camY;
	int			**textures;
	t_image	*image;
}	t_data;

void	data_init(t_data *data, t_map *map, t_image *img);
int		close_mlx(t_data *data);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
void	move_player(t_data *data);
void	draw_rays(t_data *data);
void	render_line(t_data *data, int x0, int y0, int x1, int y1, int color);
int		render(t_data *data);
double	get_angle(double angle);
double	get_angle2(double angle);
void	px_put(t_image *img, int x, int y, int color);
void	init_textures(t_data *data);

#endif
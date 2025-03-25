/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:52:48 by mlapique          #+#    #+#             */
/*   Updated: 2025/03/25 15:05:35 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <math.h>
# include "parsing.h"
# ifndef PI

#  define PI 3.14159265358979323846

# endif

# define VOLUME 48
# define WIDTH 2048
# define HEIGHT 1080
# define ANGLE_CIRCLE 360
# define ANGLE_HALF_CIRCLE 180
# define ANGLE_QUART_CIRCLE 90
# define FOV 70
# define PLAYER_WEIGHT 6
# define PRECISION 0.5
# define EAST 0
# define WEST 1
# define NORTH 2
# define SOUTH 3
// 1/60
# define MAX_FPS 0.01666666666

struct			s_eve;
struct			s_wall_necessary;

typedef void	(*t_f) (struct s_eve*, struct s_wall_necessary*, int*, int*);

typedef struct s_wall_necessary
{
	double	*distance;
	double	*angle;
	int		nb_wall;
	double	walls_height;
	int		y_end;
	int		y_start;
	bool	*north_south;
	double	*x_touch;
	double	*y_touch;
	int		i;
	bool	mo_zaik;
	t_f		*draw_function;
}					t_wall;

typedef struct s_player
{
	double		plyr_x;
	double		plyr_y;
	double		anglex;
	double		angley;
	double		anglez;
	double		fov;
}					t_player;

typedef struct s_ray
{
	double	ray_angle;
	double	wall_distance;
}					t_ray;

typedef struct mlx_data
{
	mlx_t		*mlx;
	mlx_image_t	*image;
}					t_mlx;

typedef struct s_time
{
	double	old_time;
	double	new_time;
}				t_time;

typedef struct s_point
{
	int					x;
	int					y;
	int					z;
	char				*color;
}					t_point;

typedef struct s_line_necessary
{
	t_point				p1;
	t_point				p2;
	float				grad;
}						t_line_necessary;

typedef struct s_eve
{
	t_player	*player;
	t_ray		*ray;
	uint8_t		*pixels;
	t_mlx		*mlx;
	t_map		*map;
	t_wall		*walls;
	bool		e_key_released;
	bool		map_key_released;
	bool		minimap;
	t_time		time;
}						t_eve;

void		game(t_eve *eve);
int			ini_eve(t_eve **eve, int argc, char **argv);

//draw thingy

void		last_point_steep(t_line_necessary *line, int xend, \
mlx_image_t *image, int truc);
void		first_point_steep(t_line_necessary *line, int xend, \
mlx_image_t *image, int truc);
void		line(t_line_necessary *line, mlx_image_t *image);
void		steepness_draw_line(t_line_necessary *line, float place, \
mlx_image_t *image, float grad);
void		not_steep_line(t_line_necessary *line, float place, \
mlx_image_t *image, float grad);
uint32_t	color(char *colorpoint, float opacity);

// the usefull math base

int			unit_circle(double angle, bool x_or_y);				
int			integerpart(float x);
int			roundbottom(float x);
float		floatpart(float x);
float		floatipart(float x);

//matrix

int			angle_x(t_player *player, int x, int y, int z);
int			angle_y(t_player *player, int x, int y, int z);
int			angle_z(t_player *player, int x, int y, int z);
double		angle(double angle);

// walls

void		draw_wall_height(t_wall *walls, t_eve *eve, int i);
void		draw_north_textures(t_eve *eve, t_wall *walls, int *y, int *i);
void		draw_east_textures(t_eve *eve, t_wall *walls, int *y, int *i);
void		draw_west_textures(t_eve *eve, t_wall *walls, int *y, int *i);
void		draw_south_textures(t_eve *eve, t_wall *walls, int *y, int *i);

void		draw_raycast_minimap(t_point *p2, t_eve *eve, int limit);
int			wall(t_data_map *map, mlx_image_t *image);
bool		is_player_in_wall(t_data_map *data, int x, int y);

// 3d
void		raycasting(t_eve *eve, t_wall *walls);
void		put_walls(t_eve *eve, t_wall *walls);
void		south(t_eve *eve, int *i, int *y);
void		north(t_eve *eve, int *i, int *y);
void		east(t_eve *eve, int *i, int *y);
void		west(t_eve *eve, int *i, int *y);

// gameplay

void		open_door(t_eve *eve);
void		ft_move(t_eve *eve);
void		mouse_move(void *param);

// memory
int			ini_eve_calloc(t_eve **eve, int argc, char **argv);
void		free_everything(t_eve *eve);

// colors

void		limit_colors(int *red, int *green, int *blue);
uint32_t	get_pixel(mlx_texture_t *texture, uint32_t x, uint32_t y);
uint32_t	get_color(char **colors);
void		free_game(t_wall *walls);

#endif

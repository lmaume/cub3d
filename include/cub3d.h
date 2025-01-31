/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:33:03 by mlapique          #+#    #+#             */
/*   Updated: 2025/01/29 17:19:36 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "MLX42/MLX42.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <math.h>
#ifndef PI

#define PI 3.1415926535

#endif

#define WIDTH 2048
#define HEIGHT 2048
#define ANGLE_CIRCLE 360
#define ANGLE_HALF_CIRCLE 180
#define ANGLE_QUART_CIRCLE 90
#define FOV 90



typedef struct s_player
{
 int  plyr_x;
 int  plyr_y;
 double anglex;
 double angley;
 double anglez;
 double fov;
} t_player;

typedef struct s_ray
{
 double ray_angle;
 double wall_distance;
 int  flag; // maybe a bool will see
} t_ray;


typedef struct mlx_data
{
    mlx_t *mlx;
    mlx_image_t* image;
}               t_mlx;

typedef struct s_point
{
	int					x;
	int					y;
	int					z;
	char				*color;
}						t_point;

typedef struct s_line_necessary
{
	t_point				p1;
	t_point				p2;
	float				grad;
}						t_line_necessary;

typedef struct s_eve
{
	t_player *player;
	t_ray	 *ray;
	uint8_t  *pixels;
	t_mlx	 *mlx;
}				t_eve;


void game(void* param, t_player *player, char **str);


//draw thingy

void					last_point_steep(t_line_necessary *line, int xend,
							mlx_image_t *image, int truc);
void					first_point_steep(t_line_necessary *line, int xend,
							mlx_image_t *image, int truc);
void					line(t_line_necessary *line, mlx_image_t *image);
void					steepness_draw_line(t_line_necessary *line, float place,
							mlx_image_t *image, float grad);
void					not_steep_line(t_line_necessary *line, float place,
							mlx_image_t *image, float grad);
uint32_t				color(char *colorpoint, float opacity);

// the usefull math base

int						integerpart(float x);
int						roundbottom(float x);
float					floatpart(float x);
float					floatipart(float x);

//matrix
int	angle_x(t_player *player, int x, int y, int z);
int angle_y(t_player *player, int x, int y, int z);
int angle_z(t_player *player, int x, int y, int z);

bool	my_mlx_pixel_put(mlx_image_t *image, int x, int y, unsigned int color);

// walls

int wall(char **str, mlx_image_t *image);

#endif

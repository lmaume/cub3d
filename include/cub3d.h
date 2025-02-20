#ifndef CUB3D_H
# define CUB3D_H

#include "MLX42/MLX42.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <math.h>
#include "parsing.h"

# define M_LOG2E	1.4426950408889634074	/* log_2 e */
# define M_LOG10E	0.43429448190325182765	/* log_10 e */
# define M_LN2		0.69314718055994530942	/* log_e 2 */
# define M_LN10		2.30258509299404568402	/* log_e 10 */
# define M_PI		3.14159265358979323846	/* pi */
# define M_PI_2		1.57079632679489661923	/* pi/2 */
# define M_PI_4		0.78539816339744830962	/* pi/4 */
# define M_1_PI		0.31830988618379067154	/* 1/pi */
# define M_2_PI		0.63661977236758134308	/* 2/pi */
# define M_2_SQRTPI	1.12837916709551257390	/* 2/sqrt(pi) */

#endif

#define WIDTH 2048
#define HEIGHT 2048
#define ANGLE_CIRCLE 360.0
#define ANGLE_HALF_CIRCLE 180.0
#define ANGLE_QUART_CIRCLE 90.0
#define FOV 70
#define PLAYER_WEIGHT 6
#define PRECISION 0.5


typedef struct s_wall_necessary
{
	double	*x_tab;
	double	*distance;
	int		limit;
	int		*wall_x;
	int		*wall_y;
	int		*ray_x;
	int		*ray_y;
	int		nb_wall;
	double	walls_height;
	double	y_end;
	double	y_start;
}					t_wall;


typedef struct s_player
{
	double	plyr_x;
	double	plyr_y;
	double	anglex;
	double	angley;
	double	anglez;
	double	fov;
}					t_player;

typedef struct s_ray
{
	double	ray_angle;
	double	wall_distance;
	int		flag; // maybe a bool will see
}					t_ray;

typedef struct mlx_data
{
	mlx_t		*mlx;
	mlx_image_t	*image;
}					t_mlx;

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
}					t_line_necessary;

typedef struct s_eve
{
	t_player	*player;
	t_ray		*ray;
	uint8_t		*pixels;
	t_mlx	 	*mlx;
	t_map		*map;
	t_wall		*walls;
	t_point		*p2;
	bool		e_key_released;
}					t_eve;


void	game(t_eve *eve);
int		ini_eve(t_eve **eve, char **argv);

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
int	angle_y(t_player *player, int x, int y, int z);
int	angle_z(t_player *player, int x, int y, int z);

// walls
int		wall(t_data_map *map, mlx_image_t *image);
int		get_volume(int height, int width);
bool	is_player_in_wall(t_data_map *data, int x, int y);

// 3d
void	put_wall_height(t_eve *eve, t_wall *walls);

// gameplay
void	open_door(t_eve *eve);
void	ft_move(t_eve *eve);

// memory
void	free_everything(t_eve *eve);

void	my_mlx_pixel_put(mlx_image_t *image, int x, int y, uint32_t color);

#endif

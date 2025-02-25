#include "../include/cub3d.h"
#include "limits.h"

static double	get_ray_distance(t_eve *eve, t_wall *walls, \
											double offset_angle)
{
	double	angle;
	double	ray_x;
	double	ray_y;
	int		tile_x;
	int		tile_y;

	angle = eve->player->anglez + offset_angle;
	ray_x = eve->player->plyr_x;
	ray_y = eve->player->plyr_y;
	ray_x += cos(angle) / (eve->player->plyr_x - floor((int)eve->player->plyr_x / 48) * 48);
	ray_y += sin(angle) / (eve->player->plyr_y - floor((int)eve->player->plyr_y / 48) * 48);
	while (1)
	{
		tile_x = floor((ray_x) / 48);
		tile_y = floor((ray_y) / 48);
		if (ray_x > WIDTH * 48 || ray_x < 0 || ray_y > HEIGHT * 48 || ray_y < 0)
			return (sqrt(pow(ray_x - eve->player->plyr_x, 2) + \
								pow(ray_y - eve->player->plyr_y, 2)));
		if (isset(eve->map->data.map[tile_y][tile_x], "1D") == 1)
		{
			walls->wall_x[walls->nb_wall] = tile_x;
			walls->wall_y[walls->nb_wall] = tile_y;
			return (init_distance(eve, walls, ray_x, ray_y, angle));
		}
		ray_x += cos(angle) * 0.1;
		ray_y += sin(angle) * 0.1;
	}
}

int	raycasting(t_eve *eve, t_wall *walls, t_point *p2)
{
	int					j;
	double				i;
	double				angle_offset;
	double				x;

	p2[0].color = "0xFF0000FF";
	i = PRECISION;
	j = 0;
	x = 0;
	walls->x_tab[j] = 0;
	while (i < FOV)
	{
		angle_offset = ((i - (FOV / 2.0)) * (PI / ANGLE_HALF_CIRCLE));
		walls->distance[j] = \
			get_ray_distance(eve, walls, angle_offset) * cos(angle_offset);
		p2[j].x = (eve->player->plyr_x + cos(eve->player->anglez + \
		angle_offset) * walls->distance[j]) / 4 + eve->map->data.volume / 8;
		p2[j].y = (eve->player->plyr_y + sin(eve->player->anglez + \
									angle_offset) * walls->distance[j]) / 4;
		p2[j].z = 0;
		x += (WIDTH / (FOV / PRECISION));
		j++;
		walls->x_tab[j] = x;
		i += PRECISION;
	}
	return (j);
}

static int	character(mlx_image_t *image, double x, double y, int r)
{
	double	i;
	double	angle;
	double	x1;
	double	y1;

	i = 0;
	while (r > 0)
	{
		while (i < ANGLE_CIRCLE)
		{
			angle = i;
			x1 = r * cos(angle * PI / ANGLE_HALF_CIRCLE);
			y1 = r * sin(angle * PI / ANGLE_HALF_CIRCLE);
			mlx_put_pixel(image, x1 + x, y1 + y, 0xFFFF00FF);
			i += 2;
		}
		i = 0;
		r--;
	}
	return (0);
}

void	free_game(t_wall *walls, t_point *p2)
{
	free(walls->distance);
	free(walls->x_tab);
	free(p2);
	free(walls->wall_x);
	free(walls->wall_y);
	free(walls->ray_x);
	free(walls->ray_y);
	free(walls);
}

void	game(t_eve *eve)
{
	eve->walls->limit = raycasting(eve, eve->walls, eve->p2);
	put_walls(eve, eve->walls);
	if (eve->minimap == true)
	{
		wall(&eve->map->data, eve->mlx->image);
		character(eve->mlx->image, eve->player->plyr_x / 4, \
						eve->player->plyr_y / 4, PLAYER_WEIGHT);
		printf("x=%f y=%f\n", eve->player->plyr_x, eve->player->plyr_x);
		draw_raycast_minimap(eve->p2, eve, eve->walls->limit);
	}
	eve->walls->nb_wall = 0;
}

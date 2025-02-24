#include "../include/cub3d.h"
#include "limits.h"


void	draw_raycast_minimap(t_point *p2, t_eve *eve, int limit)
{
	int					j;
	t_line_necessary	drawline;

	j = 0;
	while (j < limit)
	{
		drawline.p1.x = eve->player->plyr_x / 4;
		drawline.p1.y = eve->player->plyr_y / 4;
		drawline.p1.z = 0;
		drawline.p1.color = "0xFF0000FF";
		drawline.p2 = p2[j];
		line(&drawline, eve->mlx->image);
		j += 20;
	}
}

int	get_volume(int height, int width)
{
	int	i;
	int j;

	if (height == 0 || width == 0)
		return (-1);
	i = HEIGHT / height;
	j = WIDTH / width;
	if (i > j)
		return (48);
	return (48);
}

static double	get_ray_distance(t_player *player, t_data_map map, double offset_angle, t_wall *walls)
{
	double	angle;
	double	ray_x;
	double	ray_y;
	int		tile_x;
	int		tile_y;

	angle = player->anglez + offset_angle;
	ray_x = player->plyr_x;
	ray_y = player->plyr_y;
	while (1)
	{
		tile_x = floor((ray_x) / 48);
		tile_y = floor((ray_y) / 48);
		if (ray_x > WIDTH || ray_x < 0 || ray_y > HEIGHT || ray_y < 0)
			return (sqrt(pow(ray_x - player->plyr_x, 2) + pow(ray_y - player->plyr_y, 2)));
		if (isset(map.map[tile_y][tile_x], "1D") == 1)
		{
			walls->wall_x[walls->nb_wall] = tile_x;
			walls->wall_y[walls->nb_wall] = tile_y;
			walls->ray_x[walls->nb_wall] = ray_x;
			walls->ray_y[walls->nb_wall] = ray_y;
			walls->nb_wall += 1;
			return (sqrt(pow(ray_x - player->plyr_x, 2) + pow(ray_y - player->plyr_y, 2)));
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
	i = 0.3;
	j = 0;
	x = 0;
	walls->x_tab[j] = 0;
	while (i < FOV)
	{
		angle_offset = ((i - (FOV / 2.0)) * (PI / ANGLE_CIRCLE)); 
		walls->distance[j] = get_ray_distance(eve->player, eve->map->data, angle_offset, walls) * cos(angle_offset);
		p2[j].x = (eve->player->plyr_x + cos(eve->player->anglez + angle_offset) * walls->distance[j]) / 4 + eve->map->data.volume / 8;
		p2[j].y = (eve->player->plyr_y + sin(eve->player->anglez + angle_offset) * walls->distance[j]) / 4;
		p2[j].z = 0;
		x += (WIDTH / (FOV / 0.3));
		j++;
		walls->x_tab[j] = x;
		i += 0.3;
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

static void	free_game(t_wall *walls, t_point *p2)
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
	t_wall	*walls;
	t_point *p2;

	walls = ft_calloc(sizeof(t_wall), 1);
	walls->wall_x = ft_calloc(sizeof(int *), FOV/0.3 + 1);
	walls->wall_y = ft_calloc(sizeof(int *), FOV/0.3 + 1);
	walls->ray_x = ft_calloc(sizeof(int *), FOV/0.3 + 1);
	walls->ray_y = ft_calloc(sizeof(int *), FOV/0.3 + 1);
	walls->nb_wall = 0;
	p2 = ft_calloc(sizeof(t_point), FOV/0.3 + 1);
	walls->distance = ft_calloc(FOV/0.3 + 1, sizeof(double));
	walls->x_tab = ft_calloc((WIDTH / (FOV / 0.3) * FOV), sizeof(double));
	walls->limit = raycasting(eve, walls, p2);
	put_walls(eve, walls);
	wall(&eve->map->data, eve->mlx->image);
	character(eve->mlx->image, eve->player->plyr_x / 4, eve->player->plyr_y / 4, PLAYER_WEIGHT);
	draw_raycast_minimap(p2, eve, walls->limit);
	free_game(walls, p2);
}

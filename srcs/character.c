#include "../include/cub3d.h"
#include "limits.h"


void	draw_raycast_minimap(t_point *p2, t_eve *eve, int limit)
{
	int					j;
	t_line_necessary	drawline;

	j = 0;
	(void)drawline;
	(void)p2;
	(void)eve;
	(void)limit;
	// while (j < limit)
	// {
	// 	drawline.p1.x = eve->player->plyr_x;
	// 	drawline.p1.y = eve->player->plyr_y;
	// 	drawline.p1.z = 0;
	// 	drawline.p1.color = "FF0000";
	// 	drawline.p2 = p2[j];
	// 	line(&drawline, eve->mlx->image);
	// 	j += 20;
	// }
}

void	draw_line(int x1, int y1, int x2, int y2, char* color, t_eve *eve)
{
	t_line_necessary	drawline;

	drawline.p1.x = x1;
	drawline.p1.y = y1;
	drawline.p1.z = 0;
	drawline.p1.color = color;
	drawline.p2.x = x2;
	drawline.p2.y = y2;
	drawline.p2.z = 0;
	drawline.p2.color = color;
	line(&drawline, eve->mlx->image);
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
		return (j);
	return (i);
}
void	lol(){}

double get_point(t_player *player, t_data_map map, double offset_angle, t_wall *walls, t_eve *eve)
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
		tile_x = floor((ray_x) / get_volume(map.height, map.width));
		tile_y = floor((ray_y) / get_volume(map.height, map.width));
		if (tile_x < 0 || tile_x > map.width || tile_y < 0 || tile_y > map.height)
			return (0);
		walls->where_raycast_begin_x[walls->limit] = ray_x;
		walls->where_raycast_begin_y[walls->limit] = ray_y;
		if (isset(map.map[tile_y][tile_x], "1D") == 1)
		{
			// printf("x = %d (%c)   y = %d\n", tile_x, tile_y, map.map[tile_y][tile_x]);
			if (offset_angle == ((PRECISION - (FOV / 2)) * (M_PI / ANGLE_HALF_CIRCLE)))
			{
				lol();
				walls->distancex = ray_x;
				walls->distancey = ray_y;
				draw_line(player->plyr_x, player->plyr_y, ray_x, ray_y, "0000FF", eve);
				return (sqrt((ray_x - player->plyr_x) * (ray_x - player->plyr_x) + (ray_y - player->plyr_y) * (ray_y - player->plyr_y)));
			}
			else
			{
				walls->distance2x = ray_x;
				walls->distance2y = ray_y;
				draw_line(player->plyr_x, player->plyr_y, ray_x, ray_y, "0000FF", eve);
				return (sqrt((ray_x - player->plyr_x) * (ray_x - player->plyr_x) + (ray_y - player->plyr_y) * (ray_y - player->plyr_y)));
			}
		}
		ray_x += cos(angle);
		ray_y += sin(angle);
		walls->limit += 1;
	}
}

static double	get_ray_distance(t_player *player, t_data_map map, t_wall *walls, double tryx, double tryy)
{
	double	ray_x;
	double	ray_y;
	int		tile_x;
	int		tile_y;
	bool	in_wall;

	ray_x = tryx;
	ray_y = tryy;
	tile_x = floor((ray_x) / 48);
	tile_y = floor((ray_y) / 48);
	// printf("coordonne = %f   %f\n", floor(tryx / 48),  floor(tryy / 48));
	// printf("%f   %f    %d     %d\n", ray_x, ray_y, tile_x, tile_y);
	if (tile_x > 0 || tile_x < map.width - 1 || tile_y > 0 || tile_y < map.height - 1)
	{
		if (isset(map.map[tile_y][tile_x], "1D") == 1)
			in_wall = true;
	}
	while (1)
	{
		tile_x = floor((ray_x) / get_volume(map.height, map.width));
		tile_y = floor((ray_y) / get_volume(map.height, map.width));
		if (ray_x > WIDTH || ray_x < 0 || ray_y > HEIGHT || ray_y < 0)
			return (sqrt(pow(ray_x - tryx, 2) + pow(ray_y - tryy, 2)));
		// printf("ray_x = %f  ray y = %f les 2 = %f\ntilex = %d tile_y = %d\n", ray_x, ray_y, ray_x + ray_y ,tile_x, tile_y);
		if (tile_x > 0 || tile_x < map.width || tile_y > 0 || tile_y < map.height)
		{
			if (isset(map.map[tile_y][tile_x], "1D") == 1 && in_wall == false)
			{
				walls->wall_x[walls->nb_wall] = tile_x;
				walls->wall_y[walls->nb_wall] = tile_y;
				walls->ray_x[walls->nb_wall] = ray_x;
				walls->ray_y[walls->nb_wall] = ray_y;
				// printf("coordonne = %f   %f   \n", ray_y,  ray_x);
				walls->nb_wall += 1;
				return (sqrt(pow(ray_x - tryx, 2) + pow(ray_y - tryy, 2)));
			}
		}
		ray_x += cos(player->anglez);
		ray_y += sin(player->anglez);
		if (isset(map.map[tile_y][tile_x], "1D") == 0)
			in_wall = false;
	}
}

// angle_offset = ((-(FOV / 2)) * (M_PI / ANGLE_HALF_CIRCLE));  gauche
// angle_offset = (((FOV / 2)) * (M_PI / ANGLE_HALF_CIRCLE));  droite

int	raycasting(t_eve *eve, t_wall *walls, t_point *p2)
{
	int					j;
	int					kl;
	double				i;
	double				angle_offset;
	double				x;
	int					test;
	int					test2;
	double				tryx;
	double				tryy;
	double				tryx2;
	double				tryy2;


	p2[0].color = "FF0000";
	i = PRECISION;
	j = 0;
	x = 0;
	walls->x_tab[j] = 0;
	walls->limit = 0;
	angle_offset = ((PRECISION - (FOV / 2)) * (M_PI / ANGLE_HALF_CIRCLE));
	test = get_point(eve->player, eve->map->data, angle_offset, walls, eve) * (sin(FOV/2 * M_PI/180));
	angle_offset = (((FOV / 2)) * (M_PI / ANGLE_HALF_CIRCLE));
	test2 = get_point(eve->player, eve->map->data, angle_offset, walls, eve) * (sin(FOV/2*M_PI/180));
	tryx = floor(eve->player->plyr_x + test2 * cos(eve->player->anglez - M_PI_2));
	tryy = floor(eve->player->plyr_y + test2 * sin(eve->player->anglez - M_PI_2));
	tryx2 = floor(eve->player->plyr_x + test * cos(eve->player->anglez + M_PI_2));
	tryy2 = floor(eve->player->plyr_y + test * sin(eve->player->anglez + M_PI_2));
	draw_line(eve->player->plyr_x + test2 * cos(eve->player->anglez + M_PI_2), eve->player->plyr_y + test2 * sin(eve->player->anglez + M_PI_2), eve->player->plyr_x - test * cos(eve->player->anglez + M_PI_2), eve->player->plyr_y - test * sin(eve->player->anglez + M_PI_2), "FF0000FF", eve);
	draw_line(walls->distancex, walls->distancey, eve->player->plyr_x - test * cos(eve->player->anglez + M_PI_2), eve->player->plyr_y - test * sin(eve->player->anglez + M_PI_2), "FF0000FF", eve);
	draw_line(eve->player->plyr_x + test2 * cos(eve->player->anglez + M_PI_2), eve->player->plyr_y + test2 * sin(eve->player->anglez + M_PI_2), walls->distance2x, walls->distance2y, "FF0000FF", eve);
	// printf("coordonne = %f \n", (tryx - tryx2) * (tryx - tryx2) + (tryy - tryy2) * (tryy - tryy2));
	// printf("coordonne = %f   %f    %f    %f\n", tryx, tryx2, tryy, tryy2);
	// printf("coordonne = %f    %f\n", (tryx - tryx2) * (tryx - tryx2) , (tryy - tryy2) * (tryy - tryy2));
	kl = sqrt(pow(tryx - tryx2, 2) + pow(tryy - tryy2, 2));
	while (j < kl)
	{
		
		// printf("coordonne = %d\n", kl);
		walls->distance[j] = get_ray_distance(eve->player, eve->map->data, walls, tryx, tryy);
		// p2[j].x = (eve->player->plyr_x + cos(eve->player->anglez + angle_offset) * walls->distance[j]) / 4 + eve->map->data.volume / 8;
		// p2[j].y = (eve->player->plyr_y + sin(eve->player->anglez + angle_offset) * walls->distance[j]) / 4;
		// p2[j].z = 0;
		// x += (WIDTH / (FOV / PRECISION));
		draw_line(tryx, tryy, walls->ray_x[j], walls->ray_y[j], "FFFFFF", eve);
		walls->x_tab[j] = j;
		i += PRECISION;
		// printf("dist = %f\n", walls->distance[j]);
		tryx += cos(eve->player->anglez - M_PI_2);
		tryy = sin(eve->player->anglez - M_PI_2);
		j++;
	}
	printf(".\n\n\n");
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
			x1 = r * cos(angle * M_PI / ANGLE_HALF_CIRCLE);
			y1 = r * sin(angle * M_PI / ANGLE_HALF_CIRCLE);
			mlx_put_pixel(image, x1 + x, y1 + y, 0xFFFF00FF);
			i += 2;
		}
		i = 0;
		r--;
	}
	return (0);
}

void	game(t_eve *eve)
{
	eve->walls->where_raycast_begin_x = ft_calloc(20000, 1);
	eve->walls->where_raycast_begin_y = ft_calloc(20000, 1);
	eve->walls->limit = raycasting(eve, eve->walls, eve->p2);
	// printf("distance = %f\n", eve->walls->distance[1]);
	put_wall_height(eve, eve->walls);
	wall(&eve->map->data, eve->mlx->image);
	character(eve->mlx->image, eve->player->plyr_x, eve->player->plyr_y, PLAYER_WEIGHT);
	draw_raycast_minimap(eve->p2, eve, eve->walls->limit);
	eve->walls->distancex = 0;
	eve->walls->distancey = 0;
	eve->walls->nb_wall = 0;
}

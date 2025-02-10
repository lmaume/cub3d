#include "../include/cub3d.h"
#include "limits.h"

//! Sorry j'ai garde tes fonctions en commentaire j'voulais m'amuser et du coup ca marche

static double	get_ray_distance(t_player *player, t_data_map map, double offset_angle)
{
	double	angle;
	double	step;
	double	ray_x;
	double	ray_y;
	int		tile_x;
	int		tile_y;

	angle = player->anglez + offset_angle;
	step = 1.0;
	ray_x = player->plyr_x;
	ray_y = player->plyr_y;
	while (1)
	{
		tile_x = (int)(ray_x / get_volume(map.height, map.width));
		tile_y = (int)(ray_y / get_volume(map.height, map.width));
		if (tile_y < 0 || tile_y >= map.height || tile_x < 0 || tile_x >= map.width)
			break;
		if (isset(map.map[tile_y][tile_x], "1D") == 1)
			break;
		ray_x += cos(angle) * step;
		ray_y += sin(angle) * step;
	}
	return (sqrt(pow(ray_x - player->plyr_x, 2) + pow(ray_y - player->plyr_y, 2)));
}

int	raycasting(mlx_image_t *image, t_player *player, t_data_map map)
{
	t_point				p1;
	t_point				p2;
	double				i;
	double				angle_offset;
	double				distance;
	t_line_necessary	*draw_line;

	draw_line = ft_calloc(sizeof(t_line_necessary), 1);
	p1.x = player->plyr_x;
	p1.y = player->plyr_y;
	p1.z = 0;
	p1.color = "0xFF0000FF";
	p2.color = "0xFF0000FF";
	i = 0;
	while (i < FOV)
	{
		angle_offset = ((i - (FOV / 2.0)) * (PI / 180)); 
		distance = get_ray_distance(player, map, angle_offset);
		p2.x = player->plyr_x + cos(player->anglez + angle_offset) * distance;
		p2.y = player->plyr_y + sin(player->anglez + angle_offset) * distance;
		p2.z = 0;
		draw_line->p1 = p1;
		draw_line->p2 = p2;
		line(draw_line, image);
		i += 2;
	}
	free(draw_line);
	return (0);
}

// void	get_p2(t_player *player, t_data_map map, double i)
// {
// 	double	a;
// 	// t_point	p2;

// 	(void)map;
// 	a = cos(player->anglez) - ((i + FOV) / 2);
// 	// printf("angle = %f", a);
// }

// int	raycasting(mlx_image_t *image, t_player *player, t_data_map map)
// {
// 	t_point				p1;
// 	t_point				p2;
// 	double				i;
// 	double				angle;
// 	t_line_necessary	*draw_line;

// 	draw_line = ft_calloc(sizeof(t_line_necessary), 1);
// 	p1.x = player->plyr_x;
// 	p1.y = player->plyr_y;
// 	p1.z = 0;
// 	p1.color = "0xFF0000FF";
// 	p2.color = "0xFF0000FF";
// 	i = 0;
// 	while (i < FOV)
// 	{
// 		angle = i;
// 		p2.x = ((WIDTH / 2) * cos(angle * PI / ANGLE_HALF_CIRCLE));
// 		p2.y = ((HEIGHT / 2) * sin(angle * PI / ANGLE_HALF_CIRCLE));
// 		p2.z = 0;
// 		draw_line->grad = 0;
// 		draw_line->p1 = p1;
// 		draw_line->p2 = p2;
// 		get_p2(player, map, i);
// 		draw_line->p2.z = angle_z(player, p2.x, p2.y, p2.z);
// 		draw_line->p2.x = angle_x(player, p2.x, p2.y, p2.z) + player->plyr_x;
// 		draw_line->p2.y = angle_y(player, p2.x, p2.y, p2.z) + player->plyr_y;
// 		line(draw_line, image);
// 		i += 2;
// 	}
// 	free(draw_line);
// 	return (0);
// }

int	character(mlx_image_t *image, int x, int y, int r)
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
			my_mlx_pixel_put(image, x1 + x, y1 + y, 0x00FFFFFF);
			i += 5;
		}
		i = 0;
		r--;
	}
	return (0);
}

void	game(void *param, t_player *player, t_data_map map)
{
	mlx_image_t	*image;

	image = param;
	character(image, player->plyr_x, player->plyr_y, PLAYER_WEIGHT);
	raycasting(image, player, map);
}

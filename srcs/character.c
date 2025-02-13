#include "../include/cub3d.h"
#include "limits.h"

int	get_volume(int height, int width)
{
	int	i;

	i = 0;
	if (height == 0|| width == 0)
		return (-1);
	while (i * height < HEIGHT && i * width < WIDTH)
		i++;
	return (i);
}

static double	get_ray_distance(t_player *player, t_data_map map, double offset_angle)
{
	double	angle;
	double	step;
	double	ray_x;
	double	ray_y;
	int		tile_x;
	int		tile_y;

	angle = player->anglez + offset_angle;
	step = 1;
	ray_x = player->plyr_x;
	ray_y = player->plyr_y;
	while (1)
	{
		tile_x = floor((ray_x) / get_volume(map.height, map.width));
		tile_y = floor((ray_y) / get_volume(map.height, map.width));
		if (tile_y < 0 || tile_y >= map.height || tile_x < 0 || tile_x >= map.width)
			break;
		if (isset(map.map[tile_y][tile_x], "1D") == 1)
			break;
		ray_x += cos(angle) * step;
		ray_y += sin(angle) * step;
	}
	return (sqrt(pow(ray_x - player->plyr_x, 2) + pow(ray_y - player->plyr_y, 2)));
}

int	raycasting(mlx_image_t *image, t_player *player, t_data_map map, t_eve *eve)
{
	t_point				p1;
	t_point				p2;
	double				x;
	double				i;
	double				angle_offset;
	double				distance;
	t_line_necessary	*draw_line;

	draw_line = ft_calloc(sizeof(t_line_necessary), 1);
	p1.x = player->plyr_x / 4;
	p1.y = player->plyr_y / 4;
	p1.z = 0;
	p1.color = "0xFF0000FF";
	p2.color = "0xFF0000FF";
	i = 0;
	x = 0;
	while (i < FOV)
	{
		angle_offset = ((i - (FOV / 2.0)) * (PI / 180)); 
		distance = get_ray_distance(player, map, angle_offset);
		put_wall_height(eve, image, x, distance);
		p2.x = (player->plyr_x + cos(player->anglez + angle_offset) * distance) / 4 ;
		p2.y = (player->plyr_y + sin(player->anglez + angle_offset) * distance) / 4;
		p2.z = 0;
		draw_line->p1 = p1;
		draw_line->p2 = p2;
		line(draw_line, image);
		x += (WIDTH / (FOV / 0.3));
		i += 0.3;
	}
	free(draw_line);
	return (0);
}

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
			my_mlx_pixel_put(image, x1 + x, y1 + y, 0xFFFF00FF);
			i += 2;
		}
		i = 0;
		r--;
	}
	return (0);
}

void	game(t_eve *eve)
{
	character(eve->mlx->image, eve->player->plyr_x / 4, eve->player->plyr_y / 4, PLAYER_WEIGHT);
	raycasting(eve->mlx->image, eve->player, eve->map->data, eve);
}

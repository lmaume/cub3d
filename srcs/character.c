#include "../include/cub3d.h"
#include "limits.h"

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

void	free_game(t_wall *walls)
{
	free(walls->distance);
	free(walls->angle);
	free(walls->north_south);
	free(walls->x_touch);
	free(walls->y_touch);
	free(walls->draw_function);
	free(walls);
}

void	game(t_eve *eve)
{
	raycasting(eve, eve->walls);
	put_walls(eve, eve->walls);
	if (eve->minimap == true)
	{
		wall(&eve->map->data, eve->mlx->image);
		character(eve->mlx->image, eve->player->plyr_x / 8, \
			eve->player->plyr_y / 8, PLAYER_WEIGHT);
	}
}

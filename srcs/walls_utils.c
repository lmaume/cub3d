#include "../include/cub3d.h"

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
	int	j;

	if (height == 0 || width == 0)
		return (-1);
	i = HEIGHT / height;
	j = WIDTH / width;
	if (i > j)
		return (48);
	return (48);
}

double	init_distance(t_eve *eve, t_wall *walls, double ray_x, double ray_y)
{
	walls->ray_x[walls->nb_wall] = ray_x;
	walls->ray_y[walls->nb_wall] = ray_y;
	walls->nb_wall += 1;
	return (sqrt(pow(ray_x - eve->player->plyr_x, 2) + \
					pow(ray_y - eve->player->plyr_y, 2)));
}

void	draw_wall_height(t_wall *walls, t_eve *eve, int i)
{
	int		y;

	y = (HEIGHT / 2) - (walls->walls_height / 2);
	while (y < walls->y_end)
	{
		if (walls->x_tab[i] >= 0 && walls->x_tab[i] < \
							WIDTH && y >= 0 && y < HEIGHT)
		{
			draw_north_south_textures(eve, walls, &y, &i);
			draw_east_west_textures(eve, walls, &y, &i);
		}
		y++;
	}
}

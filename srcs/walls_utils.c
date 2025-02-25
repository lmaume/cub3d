#include "../include/cub3d.h"

void	draw_raycast_minimap(t_point *p2, t_eve *eve, int limit)
{
	int					j;
	t_line_necessary	drawline;

	j = 0;
	while (j < limit)
	{
		if (p2[j].x < 0 || p2[j].y < 0 || p2[j].x > WIDTH || p2[j].y > HEIGHT)
			return ;
		drawline.p1.x = eve->player->plyr_x / 4;
		drawline.p1.y = eve->player->plyr_y / 4;
		drawline.p1.z = 0;
		drawline.p1.color = "0xFF0000FF";
		drawline.p2 = p2[j];
		line(&drawline, eve->mlx->image);
		j += 20;
	}
}

int	get_volume()
{
	return (48);
}

double	init_distance(t_eve *eve, t_wall *walls, double ray_x, double ray_y, double angle)
{
	int	wall;

	wall = walls->nb_wall;
	(void)angle;
	walls->ray_x[wall] = ray_x;
	walls->ray_y[wall] = ray_y;
	walls->nb_wall += 1;
	return (sqrt(pow(walls->ray_x[wall] - eve->player->plyr_x, 2) + \
					pow(walls->ray_y[wall] - eve->player->plyr_y, 2)));
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
			draw_north_textures(eve, walls, &y, &i);
			draw_east_textures(eve, walls, &y, &i);
			draw_west_textures(eve, walls, &y, &i);
			draw_south_textures(eve, walls, &y, &i);
		}
		y++;
	}
}

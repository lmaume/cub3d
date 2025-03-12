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
		j += 200;
	}
}

void	get_wall(t_wall *walls, int *wall, int i)
{
	double	ang;

	ang = angle(walls->angle[i]);
	if (walls->north_south[i] == false)
	{
		if (ang > 0 && ang < PI)
			*wall = EAST;
		else
			*wall = WEST;
	}
	else
	{
		if (ang > PI / 2 && ang < 3 * (PI / 2))
			*wall = SOUTH;
		else
			*wall = NORTH;
	}
}

void	draw_wall_height(t_wall *walls, t_eve *eve, int i)
{
	int		y;
	int		wall;

	y = (HEIGHT * 0.5) - (walls->walls_height * 0.5);
	get_wall(walls, &wall, i);
	walls->draw_function[wall](eve, walls, &y, &i);
}

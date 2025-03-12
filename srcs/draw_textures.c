#include "../include/cub3d.h"
#include "MLX42/MLX42.h"
#include <stdint.h>

void	draw_south_textures(t_eve *eve, t_wall *walls, int *y, int *i)
{
	double			wall_h;

	wall_h = (walls->walls_height * 0.5);
	if (*i > 0 && *i < WIDTH)
	{
		while (*y < walls->y_end)
		{
			if (*y > 0 && *y < HEIGHT)
			{
				south(eve, i, y);
			}
			else if (*y < 0)
				*y += *y * -1;
			*y += 1;
		}
	}
}

void	draw_north_textures(t_eve *eve, t_wall *walls, int *y, int *i)
{
	double		wall_h;

	wall_h = (walls->walls_height * 0.5);
	if (*i > 0 && *i < WIDTH)
	{
		while (*y < walls->y_end)
		{
			if (*y > 0 && *y < HEIGHT)
			{
				north(eve, i, y);
			}
			else if (*y < 0)
				*y += *y * -1;
			*y += 1;
		}
	}
}

void	draw_east_textures(t_eve *eve, t_wall *walls, int *y, int *i)
{
	double		wall_h;

	wall_h = (walls->walls_height * 0.5);
	if (*i > 0 && *i < WIDTH)
	{
		while (*y < walls->y_end)
		{
			if (*y > 0 && *y < HEIGHT)
			{
				east(eve, i, y);
			}
			else if (*y < 0)
				*y += *y * -1;
			*y += 1;
		}
	}
}

void	draw_west_textures(t_eve *eve, t_wall *walls, int *y, int *i)
{
	double		wall_h;

	wall_h = (walls->walls_height * 0.5);
	if (*i > 0 && *i < WIDTH)
	{
		while (*y < walls->y_end)
		{
			if (*y > 0 && *y < HEIGHT)
			{
				west(eve, i, y);
			}
			else if (*y < 0)
				*y += *y * -1;
			*y += 1;
		}
	}
}

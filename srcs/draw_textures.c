
#include "../include/cub3d.h"
#include "MLX42/MLX42.h"
#include <stdint.h>

void	draw_south_textures(t_eve *eve, t_wall *walls, int *y, int *i)
{
	uint32_t	color;
	int			y_tex;
	int			x_tex;
	int         j;
	int         limit;

	j = 0;
	if (*i < walls->limit)
		limit = walls->x_tab[*i + 1] - walls->x_tab[*i];
	else
		limit = 1;
	while (j < limit + 1)
	{
		if (walls->ray_y[*i] == walls->wall_y[*i] * eve->map->data.volume)
		{
			y_tex = ((*y) - (HEIGHT / 2) + (walls->walls_height / 2)) * \
			eve->map->data.textures.south_texture->height / walls->walls_height;
			x_tex = ((walls->ray_x[*i] % eve->map->data.volume) * \
			eve->map->data.textures.south_texture->width) / eve->map->data.volume;
			x_tex = eve->map->data.textures.south_texture->width - 1 - x_tex - j;
			color = get_pixel(eve->map->data.textures.south_texture, x_tex, y_tex);
			if (walls->x_tab[*i] - j > 0)
				mlx_put_pixel(eve->mlx->image, walls->x_tab[*i] - j, *y, color);
		}
		j++;
	}
}

void	draw_north_textures(t_eve *eve, t_wall *walls, int *y, int *i)
{
	uint32_t	color;
	int			y_tex;
	int			x_tex;


	int         j;
	int         limit;

	j = 0;
	if (*i < walls->limit)
		limit = walls->x_tab[*i + 1] - walls->x_tab[*i];
	else
		limit = 1;
	while (j < limit + 1)
	{
		if (walls->ray_y[*i] == (walls->wall_y[*i] * \
							eve->map->data.volume) + eve->map->data.volume - 1)
		{
			y_tex = ((*y) - (HEIGHT / 2) + (walls->walls_height / 2)) * \
			eve->map->data.textures.north_texture->height / walls->walls_height;
			x_tex = ((walls->ray_x[*i] % eve->map->data.volume) * \
			eve->map->data.textures.north_texture->width) / eve->map->data.volume + j;
			color = get_pixel(eve->map->data.textures.north_texture, x_tex, y_tex);
			mlx_put_pixel(eve->mlx->image, walls->x_tab[*i] + j, *y, color);
		}
		j++;
	}
}

void	draw_east_textures(t_eve *eve, t_wall *walls, int *y, int *i)
{
	uint32_t	color;
	int			y_tex;
	int			x_tex;
	int         j;
	int         limit;

	j = 0;
	if (*i < walls->limit)
		limit = (walls->x_tab[*i + 1] - walls->x_tab[*i]);
	else
		limit = 1;
	while (j < limit + 1)
	{
		if (walls->ray_x[*i] == walls->wall_x[*i] * eve->map->data.volume)
		{
			y_tex = ((*y) - (HEIGHT / 2) + (walls->walls_height / 2)) \
			* eve->map->data.textures.east_texture->height / walls->walls_height;
			x_tex = ((((walls->ray_y[*i]) % eve->map->data.volume) * \
			eve->map->data.textures.east_texture->width) / eve->map->data.volume) + j;
			color = get_pixel(eve->map->data.textures.east_texture, x_tex, y_tex);
			mlx_put_pixel(eve->mlx->image, walls->x_tab[*i] + j, *y, color);
		}
	j++;
	}
}

void	draw_west_textures(t_eve *eve, t_wall *walls, int *y, int *i)
{
	uint32_t	color;
	int			y_tex;
	int			x_tex;
	int         j;
	int         limit;

	j = 0;
	if (*i < walls->limit)
		limit = walls->x_tab[*i + 1] - walls->x_tab[*i];
	else
		limit = 1;
	while (j < limit + 1)
	{
		if (walls->ray_x[*i] == (walls->wall_x[*i] * \
							eve->map->data.volume) + eve->map->data.volume - 1)
		{
			y_tex = ((*y) - (HEIGHT / 2) + (walls->walls_height / 2)) * \
			eve->map->data.textures.west_texture->height / walls->walls_height;
			x_tex = (((walls->ray_y[*i]) % eve->map->data.volume) * \
			(eve->map->data.textures.west_texture->width) / eve->map->data.volume) - j;
			x_tex = eve->map->data.textures.west_texture->width - 1 - x_tex;
			color = get_pixel(eve->map->data.textures.west_texture, x_tex, y_tex);
			if (walls->x_tab[*i] - j > 0)
				mlx_put_pixel(eve->mlx->image, walls->x_tab[*i] - j, *y, color);
		}
		j++;
	}
}

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"
#include <stdint.h>

static void	draw_ceiling(int y_end, int x, mlx_image_t *image, t_data_map *data)
{
	int			line_width;
	int			x_temp;
	int			y;
	char		**colors;
	uint32_t	color;

	colors = ft_split(data->ceiling, ',');
	color = get_color(colors);
	y = 0;
	while (y < y_end)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		{
			line_width = 11;
			x_temp = x;
			while (line_width > 0)
			{
				mlx_put_pixel(image, x_temp, y, color);
				x_temp++;
				line_width--;
			}
		}
		y++;
	}
	free_tab(colors);
}

static void	draw_floor(int y, int x, mlx_image_t *image, t_data_map *data)
{
	int			line_width;
	int			x_temp;
	char		**colors;
	uint32_t	color;

	colors = ft_split(data->floor, ',');
	color = get_color(colors);
	while (y < HEIGHT)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y <= HEIGHT)
		{
			line_width = 11;
			x_temp = x;
			while (line_width > 0)
			{
				mlx_put_pixel(image, x_temp, y, color);
				x_temp++;
				line_width--;
			}
		}
		y++;
	}
	free_tab(colors);
}

void	draw_north_south_textures(t_eve *eve, t_wall *walls, int *y, int *i)
{
	uint32_t	color;
	int			y_tex;
	int			x_tex;

	if (walls->ray_y[*i] == walls->wall_y[*i] * eve->map->data.volume)
	{
		y_tex = ((*y) - (HEIGHT / 2) + (walls->walls_height / 2)) * \
		eve->map->data.textures.south_texture->height / walls->walls_height;
		x_tex = ((walls->ray_x[*i] % eve->map->data.volume) * \
		eve->map->data.textures.south_texture->width) / eve->map->data.volume;
		x_tex = eve->map->data.textures.south_texture->width - 1 - x_tex;
		color = get_pixel(eve->map->data.textures.south_texture, x_tex, y_tex);
		mlx_put_pixel(eve->mlx->image, walls->x_tab[*i], *y, color);
	}
	else if (walls->ray_y[*i] == (walls->wall_y[*i] * \
						eve->map->data.volume) + eve->map->data.volume - 1)
	{
		y_tex = ((*y) - (HEIGHT / 2) + (walls->walls_height / 2)) * \
		eve->map->data.textures.north_texture->height / walls->walls_height;
		x_tex = ((walls->ray_x[*i] % eve->map->data.volume) * \
		eve->map->data.textures.north_texture->width) / eve->map->data.volume;
		color = get_pixel(eve->map->data.textures.north_texture, x_tex, y_tex);
		mlx_put_pixel(eve->mlx->image, walls->x_tab[*i], *y, color);
	}
}

void	draw_east_west_textures(t_eve *eve, t_wall *walls, int *y, int *i)
{
	uint32_t	color;
	int			y_tex;
	int			x_tex;

	if (walls->ray_x[*i] == walls->wall_x[*i] * eve->map->data.volume)
	{
		y_tex = ((*y) - (HEIGHT / 2) + (walls->walls_height / 2)) \
		* eve->map->data.textures.east_texture->height / walls->walls_height;
		x_tex = ((walls->ray_y[*i] % eve->map->data.volume) * \
		eve->map->data.textures.east_texture->width) / eve->map->data.volume;
		color = get_pixel(eve->map->data.textures.east_texture, x_tex, y_tex);
		mlx_put_pixel(eve->mlx->image, walls->x_tab[*i], *y, color);
	}
	else if (walls->ray_x[*i] == (walls->wall_x[*i] * \
						eve->map->data.volume) + eve->map->data.volume - 1)
	{
		y_tex = ((*y) - (HEIGHT / 2) + (walls->walls_height / 2)) * \
		eve->map->data.textures.west_texture->height / walls->walls_height;
		x_tex = ((walls->ray_y[*i]) % eve->map->data.volume) * \
		(eve->map->data.textures.west_texture->width) / eve->map->data.volume;
		x_tex = eve->map->data.textures.west_texture->width - 1 - x_tex;
		color = get_pixel(eve->map->data.textures.west_texture, x_tex, y_tex);
		mlx_put_pixel(eve->mlx->image, walls->x_tab[*i], *y, color);
	}
}

//! les textures s'affichent comme de la merde quand la map est grande !//
void	put_walls(t_eve *eve, t_wall *walls)
{
	int		i;

	i = 0;
	while (i < walls->limit)
	{
		walls->walls_height = ((HEIGHT * 30) / walls->distance[i]);
		walls->y_start = (HEIGHT / 2) - (walls->walls_height / 2);
		walls->y_end = (HEIGHT / 2) + (walls->walls_height / 2);
		draw_ceiling(walls->y_start, (int)walls->x_tab[i], \
							eve->mlx->image, &eve->map->data);
		draw_wall_height(walls, eve, i);
		draw_floor(walls->y_end, (int)walls->x_tab[i], \
							eve->mlx->image, &eve->map->data);
		i++;
	}
}

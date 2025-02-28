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
	while (y <= y_end + 8)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		{
			line_width = WIDTH * PRECISION / 48;
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
			line_width = WIDTH * PRECISION / 48;
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
		draw_floor(walls->y_end - 8, (int)walls->x_tab[i], \
							eve->mlx->image, &eve->map->data);
		draw_wall_height(walls, eve, i);
		i++;
	}
}

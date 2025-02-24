#include "../include/cub3d.h"
#include "MLX42/MLX42.h"
#include <stdint.h>

static uint32_t 	get_color(char **colors)
{
	uint32_t	color;

	color = 0;
	color += ft_atoi(colors[0], NULL) << 24;
	color += ft_atoi(colors[1], NULL) << 16;
	color += ft_atoi(colors[2], NULL) << 8; 
	color += 255;
	return (color);
}

static void draw_ceiling(double y_end, double x, mlx_image_t *image, t_data_map *data)
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
			x_temp = x;
			line_width = 17;
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

static void draw_floor(double y_start, int x, mlx_image_t *image, t_data_map *data)
{
	int			line_width;
	int			x_temp;
	int			y;
	char		**colors;
	uint32_t	color;

	colors = ft_split(data->floor, ',');
	color = get_color(colors);
	y = y_start;
	while (y < HEIGHT)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y <= HEIGHT)
		{
			x_temp = x;
			line_width = 17;
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


// static void draw_wall_height(t_wall *walls, t_eve *eve, int i)
// {
// 	int		line_width;
// 	int		x_temp;
// 	int		y;
// 	mlx_texture_t* texture;


// 	y = (HEIGHT / 2) - (walls->walls_height / 2);;
// 	while (y < walls->y_end)
// 	{
// 		if (walls->x_tab[i] >= 0 && walls->x_tab[i] < WIDTH && y >= 0 && y < HEIGHT)
// 		{
// 			line_width = 1;
// 			x_temp = walls->x_tab[i];
// 			while (line_width > 0)
// 			{
// 				if (walls->ray_y[i]== walls->wall_y[i] * eve->map->data.volume)
// 					texture = mlx_load_png("textures/dave.png");
// 				else if (walls->ray_y[i] == (walls->wall_y[i] * eve->map->data.volume) + eve->map->data.volume - 1)
// 					texture = mlx_load_png("textures/dave.png");
// 				if (walls->ray_x[i]== walls->wall_x[i] * eve->map->data.volume)
// 					texture = mlx_load_png("textures/dave.png");
// 				else if (walls->ray_x[i] == (walls->wall_x[i] * eve->map->data.volume) + eve->map->data.volume - 1)
// 					texture = mlx_load_png("textures/dave.png");
// 				x_temp++;
// 				line_width--;
// 			}
// 		}
// 		y += 1000;
// 	}
// 	mlx_image_t* img = mlx_texture_to_image(eve->mlx->mlx, texture);
// 	mlx_image_to_window(eve->mlx->mlx, img, 0, 0);
// }

static void draw_wall_height(t_wall *walls, t_eve *eve, int i, int j)
{
	int		line_width;
	int		x_temp;
	int		y;
	int		tr;


	y = (HEIGHT / 2) - (walls->walls_height / 2);;
	tr = 0;
	while (y < walls->y_end)
	{
		while (tr < j)
		{
			if (walls->x_tab[i] >= 0 && walls->x_tab[i] < WIDTH && y >= 0 && y < HEIGHT)
			{
				line_width = 1;
				x_temp = walls->x_tab[i] + tr;
				while (line_width > 0)
				{
					if (walls->ray_y[i]== walls->wall_y[i] * eve->map->data.volume)
						mlx_put_pixel(eve->mlx->image, x_temp, y, (0x88FF88FF));
					else if (walls->ray_y[i] == (walls->wall_y[i] * eve->map->data.volume) + eve->map->data.volume - 1)
						mlx_put_pixel(eve->mlx->image, x_temp, y, (0xFF88FFFF));
					if (walls->ray_x[i]== walls->wall_x[i] * eve->map->data.volume)
						mlx_put_pixel(eve->mlx->image, x_temp, y, (0xFFFF88FF));
					else if (walls->ray_x[i] == (walls->wall_x[i] * eve->map->data.volume) + eve->map->data.volume - 1)
						mlx_put_pixel(eve->mlx->image, x_temp, y, (0xFFFFFFFF));
					x_temp++;
					line_width--;
				}
			}
			tr++;
		}
		y++;
	}
}

void put_wall_height(t_eve *eve, t_wall *walls)
{
	int		i;
	int		j;
	int		pas;

	i = 0;
	pas = 2048 / walls->limit;
	printf("limit = %d", pas);
	while (i < walls->limit)
	{
		walls->walls_height = ((HEIGHT * 30) / walls->distance[i]);
		walls->y_start = (HEIGHT / 2) - (walls->walls_height / 2);
		walls->y_end = (HEIGHT / 2) + (walls->walls_height / 2);
		// pas = walls->walls_height / ((HEIGHT * 30) / walls->distance[i + 1]) / 17;
		// while(j < 17)
		// {
		// 	walls->walls_height += pas;
		// 	walls->y_start += pas;
		// 	walls->y_end -= pas;
		// 	walls->x_tab[i] += 1;
		// 	j++;
		// }
		if (walls->distance[i] > 0)
		{
			while (j < pas)
			{
				draw_wall_height(walls, eve, i, j);
				draw_ceiling(walls->y_start, (int)walls->x_tab[i] + j, eve->mlx->image, &eve->map->data);
				draw_floor(walls->y_end, (int)walls->x_tab[i] + j, eve->mlx->image, &eve->map->data);
				j++;
			}
		}
		j = 0;
		i++;
	}
}

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"
#include <stdint.h>

// static uint32_t get_pixel_color(mlx_texture_t* texture, uint32_t x, uint32_t y)
// {
//     if (x >= texture->width || y >= texture->height)
//     {
//         // Coordonnées en dehors de la texture
//         return 0;
//     }

//     // Calculer l'index du pixel dans le tableau
//     uint32_t index = (y * texture->width + x) * 4;

//     // Récupérer les valeurs RGBA
//     uint8_t r = texture->pixels[index];
//     uint8_t g = texture->pixels[index + 1];
//     uint8_t b = texture->pixels[index + 2];
//     uint8_t a = texture->pixels[index + 3];

//     // Combiner les canaux en une seule valeur uint32_t
//     uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;
//     return color;
// }

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
			line_width = 15;
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
			line_width = 15;
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

static void draw_wall_height(t_wall *walls, t_eve *eve, int i, double test, double test2)
{
	int		line_width;
	int		x_temp;
	double	y;
	int		truc;
	double	pas;

	y = (HEIGHT / 2) - (test / 2);
	truc = (HEIGHT / 2) - (test2 / 2);
	pas = y / truc;
	while (y < walls->y_end)
	{
		if (walls->x_tab[i] >= 0 && walls->x_tab[i] < WIDTH && y >= 0 && y < HEIGHT)
		{
			x_temp = walls->x_tab[i];
			line_width = 17;
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
		y++;
	}
}

void put_wall_height(t_eve *eve, t_wall *walls)
{
	int		i;
	double	test;
	double 	test2;
	int		wallx;
	int		wally;
	double pas;

	i = 0;
	wallx = walls->wall_x[i];
	wally = walls->wall_y[i];
	test = ((HEIGHT * 30) / (walls->distance[i]));
	while (wallx == walls->wall_x[i] && wally == walls->wall_y[i])
		i++;
	test2 = ((HEIGHT * 30) / (walls->distance[i]));
	pas = (test2 / test);
	i = 0;
	printf("%f   %f    %f\n", test, test2, pas);
	walls->walls_height = ((HEIGHT * 30) / (walls->distance[i]));
	while (i < walls->limit)
	{
		if (walls->wall_x[i] == wallx && wally == walls->wall_y[i])
		{
			if (i < walls->limit / 2)
				test -= pas;
			walls->walls_height = test;
		}
		else
		{
			wallx = walls->wall_x[i];
			wally = walls->wall_y[i];
			test = walls->walls_height = ((HEIGHT * 30) / (walls->distance[i]));
			if (i + 20 < walls->limit)
				test2 = walls->walls_height = ((HEIGHT * 30) / (walls->distance[i + 20]));
			else
				test2 = walls->walls_height = ((HEIGHT * 30) / (walls->distance[walls->limit - 1]));
			pas = (test2 / test); 
		}
		walls->y_end = (HEIGHT / 2) + (walls->walls_height / 2);
		walls->y_start = (HEIGHT / 2) - (walls->walls_height / 2);
		draw_ceiling(walls->y_start, walls->x_tab[i], eve->mlx->image, &eve->map->data);
		draw_floor(walls->y_end, (int)walls->x_tab[i], eve->mlx->image, &eve->map->data);
		draw_wall_height(walls, eve, i, test, test2);
		i++;
	}
}

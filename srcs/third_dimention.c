#include "../include/cub3d.h"
#include "MLX42/MLX42.h"
#include <stdint.h>

static uint32_t get_pixel_color(mlx_texture_t* texture, uint32_t x, uint32_t y)
{
    if (x >= texture->width || y >= texture->height)
    {
        // Coordonnées en dehors de la texture
        return 0;
    }

    // Calculer l'index du pixel dans le tableau
    uint32_t index = (y * texture->width + x) * 4;

    // Récupérer les valeurs RGBA
    uint8_t r = texture->pixels[index];
    uint8_t g = texture->pixels[index + 1];
    uint8_t b = texture->pixels[index + 2];
    uint8_t a = texture->pixels[index + 3];

    // Combiner les canaux en une seule valeur uint32_t
    uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;
    return color;
}

static void	limit_colors(int *red, int *green, int *blue)
{
	if (*red > 255)
		*red = 255;
	if (*red < 0)
		*red = 0;
	if (*green > 255)
		*green = 255;
	if (*green < 0)
		*green = 0;
	if (*blue > 255)
		*blue = 255;
	if (*blue < 0)
		*blue = 0;
}

static uint32_t 	get_color(char **colors)
{
	uint32_t	color;
	int			red;
	int			green;
	int			blue;

	red = ft_atoi(colors[0], NULL);
	green = ft_atoi(colors[1], NULL);
	blue = ft_atoi(colors[2], NULL);
	limit_colors(&red, &blue, &green);
	color = 0;
	color += red << 24;
	color += green << 16;
	color += blue << 8; 
	color += 255;
	return (color);
}

static void draw_ceiling(int y_end, int x, mlx_image_t *image, t_data_map *data)
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

static void draw_floor(int y_start, int x, mlx_image_t *image, t_data_map *data)
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

static void	draw_north_south_textures(t_eve *eve, t_wall *walls, int *y, int *i)
{
	uint32_t	color;
	int			y_texture;
	int			x_texture;

	if (walls->ray_y[*i] == walls->wall_y[*i] * eve->map->data.volume)
	{
		y_texture = ((*y) - (HEIGHT / 2) + (walls->walls_height / 2)) * eve->map->data.textures.south_texture->height / walls->walls_height;
		x_texture = ((walls->ray_x[*i] % eve->map->data.volume) * eve->map->data.textures.south_texture->width) / eve->map->data.volume;
		color = get_pixel_color(eve->map->data.textures.south_texture, x_texture, y_texture);
		mlx_put_pixel(eve->mlx->image, walls->x_tab[*i], *y, color);
	}
	else if (walls->ray_y[*i] == (walls->wall_y[*i] * eve->map->data.volume) + eve->map->data.volume - 1)
	{
		y_texture = ((*y) - (HEIGHT / 2) + (walls->walls_height / 2)) * eve->map->data.textures.north_texture->height / walls->walls_height;
		x_texture = ((walls->ray_x[*i] % eve->map->data.volume) * eve->map->data.textures.north_texture->width) / eve->map->data.volume;
		color = get_pixel_color(eve->map->data.textures.north_texture, x_texture, y_texture);
		mlx_put_pixel(eve->mlx->image, walls->x_tab[*i], *y, color);
	}
}

static void	draw_east_west_textures(t_eve *eve, t_wall *walls, int *y, int *i)
{
	uint32_t	color;
	int			y_texture;
	int			x_texture;

	if (walls->ray_x[*i]== walls->wall_x[*i] * eve->map->data.volume)
	{
		y_texture = ((*y) - (HEIGHT / 2) + (walls->walls_height / 2)) * eve->map->data.textures.east_texture->height / walls->walls_height;
		x_texture = ((walls->ray_y[*i] % eve->map->data.volume) * eve->map->data.textures.east_texture->width) / eve->map->data.volume;
		color = get_pixel_color(eve->map->data.textures.east_texture, x_texture, y_texture);
		mlx_put_pixel(eve->mlx->image, walls->x_tab[*i], *y, color);
	}
	else if (walls->ray_x[*i] == (walls->wall_x[*i] * eve->map->data.volume) + eve->map->data.volume - 1)
	{
		y_texture = ((*y) - (HEIGHT / 2) + (walls->walls_height / 2)) * eve->map->data.textures.west_texture->height / walls->walls_height;

		x_texture = ((walls->ray_y[*i]) % eve->map->data.volume) * (eve->map->data.textures.west_texture->width) / eve->map->data.volume;
		color = get_pixel_color(eve->map->data.textures.west_texture, x_texture, y_texture);
		mlx_put_pixel(eve->mlx->image, walls->x_tab[*i], *y, color);
	}
}

static void draw_wall_height(t_wall *walls, t_eve *eve, int i)
{
	int		y;

	y = (HEIGHT / 2) - (walls->walls_height / 2);;
	while (y < walls->y_end)
	{
		if (walls->x_tab[i] >= 0 && walls->x_tab[i] < WIDTH && y >= 0 && y < HEIGHT)
		{
			draw_north_south_textures(eve, walls, &y, &i);
			draw_east_west_textures(eve, walls, &y, &i);
		}
		y++;
	}
}

void put_walls(t_eve *eve, t_wall *walls)
{
	int		i;

	i = 0;
	while (i < walls->limit)
	{
		walls->walls_height = ((HEIGHT * 30) / walls->distance[i]);
		walls->y_start = (HEIGHT / 2) - (walls->walls_height / 2);
		walls->y_end = (HEIGHT / 2) + (walls->walls_height / 2);
		draw_ceiling(walls->y_start, (int)walls->x_tab[i], eve->mlx->image, &eve->map->data);
		draw_wall_height(walls, eve, i);
		draw_floor(walls->y_end, (int)walls->x_tab[i], eve->mlx->image, &eve->map->data);
		i++;
	}
}

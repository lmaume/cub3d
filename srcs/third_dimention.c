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

static void draw_ceiling(int y_end, int x, mlx_image_t *image)
{
	int		line_width;
	int		x_temp;
	int		y;

	y = 0;
	while (y < y_end)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		{
			line_width = 11;
			x_temp = x;
			while (line_width > 0)
			{
				mlx_put_pixel(image, x_temp, y, (0xAAFFFFFF));
				x_temp++;
				line_width--;
			}
		}
		y++;
	}
}

static void draw_floor(int y_start, int x, mlx_image_t *image)
{
	int		line_width;
	int		x_temp;
	int		y;

	y = y_start;
	while (y < HEIGHT)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y <= HEIGHT)
		{
			line_width = 11;
			x_temp = x;
			while (line_width > 0)
			{
				mlx_put_pixel(image, x_temp, y, (0xAADDAAFF));
				x_temp++;
				line_width--;
			}
		}
		y++;
	}
}

static void draw_wall_height(double wall_height, int y_end, int x, t_eve *eve)
{
	uint32_t	color;
	int			y_texture;
	int			x_texture;
	int			y;

	y = (HEIGHT / 2) - (wall_height / 2);
	while (y < y_end)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		{
			y_texture = ((y - (HEIGHT / 2) + (wall_height / 2)) * eve->map->data.textures.north_texture->height) / wall_height;
			// x_texture = x * eve->map->data.textures.north_texture->width;
			x_texture = x % eve->map->data.textures.north_texture->width;
			color = get_pixel_color(eve->map->data.textures.north_texture, x_texture, y_texture);	
			mlx_put_pixel(eve->mlx->image, x, y, color);
		}
		y++;
	}
}

void put_wall_height(t_eve *eve, mlx_image_t *image, int x, double distance)
{
	double	wall_height;
	int		y_start;
	int		y_end;

	wall_height = (HEIGHT * 30) / distance;
	y_start = (HEIGHT / 2) - (wall_height / 2);
	y_end = (HEIGHT / 2) + (wall_height / 2);
	draw_ceiling(y_start, x, image);
	draw_wall_height(wall_height, y_end, x, eve);
	draw_floor(y_end, x, image);
}

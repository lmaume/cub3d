#include "../include/cub3d.h"

static void	draw_floor(int i, int j, mlx_image_t *image, int decal)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (a < decal)
	{
		while (b < decal)
		{
			my_mlx_pixel_put(image, i + a, j + b, 0x222222FF);
			b++;
		}
		b = 0;
		a++;
	}
}

static void	draw_wall(int i, int j, mlx_image_t *image, int decal)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (a < decal)
	{
		while (b < decal)
		{
			my_mlx_pixel_put(image, i + a, j + b, 0x777777FF);
			b++;
		}
		b = 0;
		a++;
	}
}

static void	draw_close_door(int i, int j, mlx_image_t *image, int decal)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (a < volume)
	{
		while (b < volume)
		{
			my_mlx_pixel_put(image, i + a, j + b, 0xC22222FF);
			b++;
		}
		b = 0;
		a++;
	}
}

static void	draw_open_door(int i, int j, mlx_image_t *image, int decal)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (a < volume)
	{
		while (b < volume)
		{
			my_mlx_pixel_put(image, i + a, j + b, 0x8B4513FF);
			b++;
		}
		b = 0;
		a++;
	}
}

int	wall(t_data_map *map, mlx_image_t *image)
{
	int	i;
	int	j;

	decal = get_volume(map->height, map->width) / 4;
	j = 0;
	i = 0;
	while (map->map[i])
	{
		while (map->map[i][j])
		{
			if (map->map[i][j] == '1')
				draw_wall(j * 1.05 * decal, i * 1.05 * decal, image, decal * 1.07);
			if (isset(map->map[i][j], "0NSEW") == 1)
				draw_floor(j * 1.05 * decal, i * 1.05 * decal, image, decal * 1.07);
			if (map->map[i][j] == 'D')
				draw_close_door(j * 1.05 * decal, i * 1.05 * decal, image, decal * 1.07);
			if (map->map[i][j] == 'O')
				draw_open_door(j * 1.05 * decal, i * 1.05 * decal, image, decal * 1.07);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

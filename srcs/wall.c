#include "../include/cub3d.h"

int	get_volume(int height, int width)
{
	int	i;

	i = 0;
	while (i * height < HEIGHT && i * width < WIDTH)
		i++;
	return (i);
}

void	draw_wall(int i, int j, mlx_image_t *image, int decal)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (a < decal)
	{
		while (b < decal)
		{
			my_mlx_pixel_put(image, i + a, j + b, 0xAA0303FF);
			b++;
		}
		b = 0;
		a++;
	}
}

void	draw_close_door(int i, int j, mlx_image_t *image, int decal)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (a < decal)
	{
		while (b < decal)
		{
			my_mlx_pixel_put(image, i + a, j + b, 0xDDDD03FF);
			b++;
		}
		b = 0;
		a++;
	}
}

void	draw_open_door(int i, int j, mlx_image_t *image, int decal)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (a < decal)
	{
		while (b < decal)
		{
			my_mlx_pixel_put(image, i + a, j + b, 0x888803FF);
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
	int	decal;

	decal = get_volume(map->height, map->width) / 4;
	j = 0;
	i = 0;
	while (map->map[i])
	{
		while (map->map[i][j])
		{
			if (map->map[i][j] == '1')
				draw_wall(j * decal, i * decal, image, decal);
			if (map->map[i][j] == 'D')
				draw_close_door(j * decal, i * decal, image, decal);
			if (map->map[i][j] == 'O')
				draw_open_door(j * decal, i * decal, image, decal);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

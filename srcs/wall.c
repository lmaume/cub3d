#include "../include/cub3d.h"

int	get_volume(int height, int width)
{
	int	i;
	int j;

	i = floor(HEIGHT / height);
	j = floor(WIDTH / width);
	if (i > j)
		return (j);
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

void	draw_close_door(int i, int j, mlx_image_t *image, int volume)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (a < volume)
	{
		while (b < volume)
		{
			my_mlx_pixel_put(image, i + a, j + b, 0xDDDD03FF);
			b++;
		}
		b = 0;
		a++;
	}
}

void	draw_open_door(int i, int j, mlx_image_t *image, int volume)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (a < volume)
	{
		while (b < volume)
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

	j = 0;
	i = 0;
	while (map->map[i])
	{
		while (map->map[i][j])
		{
			if (map->map[i][j] == '1')
				draw_wall(j * map->volume, i * map->volume, image, map->volume);
			if (map->map[i][j] == 'D')
				draw_close_door(j * map->volume, i * map->volume, image, map->volume);
			if (map->map[i][j] == 'O')
				draw_open_door(j * map->volume, i * map->volume, image, map->volume);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

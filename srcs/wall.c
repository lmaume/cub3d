/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:54 by mlapique          #+#    #+#             */
/*   Updated: 2025/03/21 17:53:56 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			mlx_put_pixel(image, i + a, j + b, 0x222222FF);
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
			mlx_put_pixel(image, i + a, j + b, 0x777777FF);
			b++;
		}
		b = 0;
		a++;
	}
}

static void	draw_close_door(int i, int j, mlx_image_t *image, int volume)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (a < volume)
	{
		while (b < volume)
		{
			mlx_put_pixel(image, i + a, j + b, 0xC22222FF);
			b++;
		}
		b = 0;
		a++;
	}
}

static void	draw_open_door(int i, int j, mlx_image_t *image, int volume)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (a < volume)
	{
		while (b < volume)
		{
			mlx_put_pixel(image, i + a, j + b, 0x8B4513FF);
			b++;
		}
		b = 0;
		a++;
	}
}

int	wall(t_data_map *map, mlx_image_t *image)
{
	int		i;
	int		j;
	double	volume;

	volume = 12;
	j = 0;
	i = 0;
	while (map->map[i])
	{
		while (map->map[i][j])
		{
			if (map->map[i][j] == '1')
				draw_wall(j * volume, i * volume, image, volume);
			else if (isset(map->map[i][j], "0NSEW") == 1)
				draw_floor(j * volume, i * volume, image, volume);
			else if (map->map[i][j] == 'D')
				draw_close_door(j * volume, i * volume, image, volume);
			else if (map->map[i][j] == 'O')
				draw_open_door(j * volume, i * volume, image, volume);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

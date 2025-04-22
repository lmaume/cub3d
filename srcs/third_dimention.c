/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_dimention.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:52 by mlapique          #+#    #+#             */
/*   Updated: 2025/04/16 14:32:13 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "MLX42/MLX42.h"
#include <stdint.h>

static void	draw_ceiling(int y_end, int x, mlx_image_t *image, t_data_map *data)
{
	int			y;

	y = 0;
	while (y <= y_end)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		{
			mlx_put_pixel(image, x, y, data->color_ceiling);
		}
		y++;
	}
}

static void	draw_floor(int y, int x, mlx_image_t *image, t_data_map *data)
{
	while (y < HEIGHT)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y <= HEIGHT)
		{
			mlx_put_pixel(image, x, y, data->colot_floor);
		}
		y++;
	}
}

void	put_walls(t_eve *eve, t_wall *walls)
{
	int		i;

	i = 0;
	while (i < WIDTH)
	{
		walls->walls_height = (VOLUME / walls->distance[i]) \
		* ((WIDTH * 0.5));
		walls->y_start = (HEIGHT * 0.5) - (walls->walls_height * 0.5);
		walls->y_end = (HEIGHT * 0.5) + (walls->walls_height * 0.5);
		draw_ceiling(walls->y_start, i, eve->mlx->image, &eve->map->data);
		draw_floor(walls->y_end, i, eve->mlx->image, &eve->map->data);
		draw_wall_height(walls, eve, i);
		i++;
	}
}

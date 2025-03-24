/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:05 by mlapique          #+#    #+#             */
/*   Updated: 2025/03/21 17:53:07 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "limits.h"

static int	character(mlx_image_t *image, double x, double y, int r)
{
	double	i;
	double	angle;
	double	x1;
	double	y1;

	i = 0;
	while (r > 0)
	{
		while (i < ANGLE_CIRCLE)
		{
			angle = i;
			x1 = r * cos(angle * PI / ANGLE_HALF_CIRCLE);
			y1 = r * sin(angle * PI / ANGLE_HALF_CIRCLE);
			if (x1 + x < 0 || y1 + y < 0 || x1 + x > WIDTH || y1 + y > HEIGHT)
				break ;
			else
				mlx_put_pixel(image, x1 + x, y1 + y, 0xFFFF00FF);
			i += 2;
		}
		i = 0;
		r--;
	}
	return (0);
}

void	game(t_eve *eve)
{
	raycasting(eve, eve->walls);
	put_walls(eve, eve->walls);
	if (eve->minimap == true)
	{
		wall(&eve->map->data, eve->mlx->image);
		character(eve->mlx->image, eve->player->plyr_x / 4, \
			eve->player->plyr_y / 4, PLAYER_WEIGHT);
	}
}

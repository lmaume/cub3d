/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:41:51 by mlapique          #+#    #+#             */
/*   Updated: 2025/01/27 18:20:39 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "limits.h"


int raycasting(mlx_image_t *image, int x, int y, t_player *player)
{
	t_point p1;
	t_point p2;
	double i;
	double angle;
	t_line_necessary *test;

	test = ft_calloc(sizeof(t_line_necessary), 1);
	p1.x = x;
	p1.y = y;
	p1.z = 0;
	p1.color = "0xFF0000FF";
	p2.color = "0xFF0000FF";
	i = 0;
	while (i < ANGLE_QUART_CIRCLE)
	{
		angle = i;
		p2.x = ((WIDTH * 2)* cos(angle * PI / ANGLE_QUART_CIRCLE / 2)) ;
		p2.y = ((HEIGHT * 2) * sin(angle * PI / ANGLE_QUART_CIRCLE / 2));
		p2.z = 0;
		test->grad = 0;
		test->p1 = p1;
		test->p2 = p2;
		test->p2.z = angle_z(player, p2.x, p2.y, p2.z);
		test->p2.x = angle_x(player, p2.x, p2.y, p2.z) + x;
		test->p2.y = angle_y(player, p2.x, p2.y, p2.z) + y;
		printf("%i\n", test->p2.y);
		line(test, image);
		i += 1.5;
	}
	return (0);
}

int character(mlx_image_t *image, int x, int y, int r)
{
	double i;
	double angle;
	double x1;
	double y1;

	i = 0;
	while (r > 0)
	{
		while (i < ANGLE_CIRCLE)
		{
			angle = i;
			x1 = r * cos(angle * PI / ANGLE_HALF_CIRCLE);
			y1 = r * sin(angle * PI / ANGLE_HALF_CIRCLE);
			my_mlx_pixel_put(image, x1 + x, y1 + y, 0x00FFFFFF);
			i += 0.1;
		}
		i = 0;
		r--;
	}
	return (0);
}

void game(void *param, t_player *player)
{
	mlx_image_t *image;

	image = param;
	character(image, player->plyr_x, player->plyr_y, 10);
	raycasting(image, player->plyr_x, player->plyr_y, player);
	
}

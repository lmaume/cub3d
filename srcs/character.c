/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:41:51 by mlapique          #+#    #+#             */
/*   Updated: 2025/01/31 16:40:11 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "limits.h"

void get_p2(t_player *player, t_data_map map, double i)
{
	// t_point	p2;
	(void)map;
	double a;

	a = cos(player->anglez) - ((i + FOV) / 2);
	// printf("angle = %f", a);
}

int raycasting(mlx_image_t *image, t_player *player, t_data_map map)
{
	t_point p1;
	t_point p2;
	double i;
	double angle;
	t_line_necessary *draw_line;

	draw_line = ft_calloc(sizeof(t_line_necessary), 1);
	p1.x = player->plyr_x;
	p1.y = player->plyr_y;
	p1.z = 0;
	p1.color = "0xFF0000FF";
	p2.color = "0xFF0000FF";
	i = 0;
	while (i < FOV)
	{
		angle = i;
		p2.x = ((WIDTH / 2) * cos(angle * PI / ANGLE_HALF_CIRCLE));
		p2.y = ((HEIGHT / 2) * sin(angle * PI / ANGLE_HALF_CIRCLE));
		p2.z = 0;
		draw_line->grad = 0;
		draw_line->p1 = p1;
		draw_line->p2 = p2;
		get_p2(player, map, i);
		draw_line->p2.z = angle_z(player, p2.x, p2.y, p2.z);
		draw_line->p2.x = angle_x(player, p2.x, p2.y, p2.z) + player->plyr_x;
		draw_line->p2.y = angle_y(player, p2.x, p2.y, p2.z) + player->plyr_y;
		line(draw_line, image);
		i += 2;
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
			i += 5;
		}
		i = 0;
		r--;
	}
	return (0);
}

void game(void *param, t_player *player, t_data_map map)
{
	mlx_image_t *image;

	image = param;
	character(image, player->plyr_x, player->plyr_y, 10);
	raycasting(image, player, map);
	
}

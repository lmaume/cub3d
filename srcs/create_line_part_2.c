/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_line_part_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:09:08 by mlapique          #+#    #+#             */
/*   Updated: 2025/01/31 14:53:45 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	not_steep_line(t_line_necessary *line, float place, mlx_image_t *image,
		float grad)
{
	int		i;
	float	usefull;

	i = line->p1.x + 1;
	while (i < line->p2.x - 1)
	{
		usefull = 1 - (place - floor(place));
		my_mlx_pixel_put(image, floor(place), i, color(line->p1.color,
				usefull));
		usefull = (place - floor(place));
		my_mlx_pixel_put(image, floor(place) + 1, i, color(line->p1.color,
				usefull));
		place += grad;
		i++;
	}
}

void	steepness_draw_line(t_line_necessary *line, float place,
		mlx_image_t *image, float grad)
{
	int		i;
	float	usefull;

	i = 0;
	i = line->p1.x + 1;
	while (i < line->p2.x - 1)
	{
		usefull = 1 - (place - floor(place));
		my_mlx_pixel_put(image, i, floor(place), color(line->p1.color,
				usefull));
		usefull = (place - floor(place));
		my_mlx_pixel_put(image, i, floor(place) + 1, color(line->p1.color,
				usefull));
		place += grad;
		i++;
	}
}

void	first_point_steep(t_line_necessary *line, int xend, mlx_image_t *image,
		int truc)
{

	my_mlx_pixel_put(image, truc, xend, color(line->p1.color, 1));
	my_mlx_pixel_put(image, truc + 1, xend, color(line->p1.color, 0.5));
}

void	last_point_steep(t_line_necessary *line, int xend, mlx_image_t *image,
		int truc)
{
	my_mlx_pixel_put(image, truc, xend, color(line->p2.color, 1));
	my_mlx_pixel_put(image, truc + 1, xend, color(line->p2.color, 0.5));
}

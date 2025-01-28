/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:41:51 by mlapique          #+#    #+#             */
/*   Updated: 2025/01/28 17:13:38 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_wall(int i, int j, mlx_image_t *image)
{
	int	a;
	int b;

	a = 0;
	b = 0;
	while (a < 100)
	{
		while (b < 100)
		{
			my_mlx_pixel_put(image, i + a, j + b, 0xFF0000FF);
			b++;
		}
		b = 0;
		a++;
	}
}

int wall(char **str, mlx_image_t *image)
{
	int i;
	int j;
	int decal;

	decal = 100;
	j = 0;
	i = 0;
	while (str[i])
	{
		while (str[i][j])
		{
			if (str[i][j] == '1')
				draw_wall(i * decal, j * decal, image);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
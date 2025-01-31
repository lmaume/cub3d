/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:41:51 by mlapique          #+#    #+#             */
/*   Updated: 2025/01/29 16:10:08 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int get_volume(char **str)
{
	int i;
	int width_max;
	int height;
	int tmp;

	width_max = 0;
	i = 0;
	height = 0;
	while (str && str[i])
	{
		tmp = ft_strlen(str[i]);
		if (tmp > width_max)
			width_max = tmp;
		i++;
	}
	i = 0;
	while (i * height < HEIGHT && i * width_max < WIDTH)
		i++;
	return (i); 
}

void draw_wall(int i, int j, mlx_image_t *image, int decal)
{
	int	a;
	int b;

	a = 0;
	b = 0;
	while (a < decal)
	{
		while (b < decal)
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

	decal = get_volume(str);
	j = 0;
	i = 0;
	while (str[i])
	{
		while (str[i][j])
		{
			if (str[i][j] == '1')
				draw_wall(j * decal, i * decal, image, decal);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
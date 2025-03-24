/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:10 by mlapique          #+#    #+#             */
/*   Updated: 2025/03/21 17:53:12 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

uint32_t	get_pixel(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	uint32_t	index;
	uint32_t	color;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;

	if (x >= texture->width || y >= texture->height)
		return (0);
	index = (y * texture->width + x) * 4;
	r = texture->pixels[index];
	g = texture->pixels[index + 1];
	b = texture->pixels[index + 2];
	color = (r << 24) | (g << 16) | (b << 8) | 255;
	return (color);
}

void	limit_colors(int *red, int *green, int *blue)
{
	if (*red > 255)
		*red = 255;
	if (*red < 0)
		*red = 0;
	if (*green > 255)
		*green = 255;
	if (*green < 0)
		*green = 0;
	if (*blue > 255)
		*blue = 255;
	if (*blue < 0)
		*blue = 0;
}

uint32_t	get_color(char **colors)
{
	uint32_t	color;
	int			red;
	int			green;
	int			blue;
	int			error;

	error = 0;
	red = ft_atoi(colors[0], &error);
	green = ft_atoi(colors[1], &error);
	blue = ft_atoi(colors[2], &error);
	if (error == 1)
		return (353638911);
	limit_colors(&red, &blue, &green);
	color = 0;
	color += red << 24;
	color += green << 16;
	color += blue << 8;
	color += 255;
	return (color);
}

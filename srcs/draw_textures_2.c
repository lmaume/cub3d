/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:21:07 by mlapique          #+#    #+#             */
/*   Updated: 2025/03/21 17:53:22 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	south(t_eve *eve, int *i, int *y)
{
	uint32_t		color;
	int				y_tex;
	int				x_tex;

	y_tex = ((*y) - (HEIGHT * 0.5) + (eve->walls->walls_height * 0.5)) * \
	eve->map->data.textures.south_texture->height / eve->walls->walls_height;
	x_tex = (fmod(eve->walls->x_touch[*i], VOLUME) * \
	(eve->map->data.textures.south_texture->width) / VOLUME);
	color = get_pixel(&*eve->map->data.textures.south_texture, x_tex, y_tex);
	mlx_put_pixel(eve->mlx->image, *i, *y, color);
}

void	north(t_eve *eve, int *i, int *y)
{
	uint32_t		color;
	int				y_tex;
	int				x_tex;

	y_tex = ((*y) - (HEIGHT * 0.5) + (eve->walls->walls_height * 0.5)) * \
	eve->map->data.textures.north_texture->height / eve->walls->walls_height;
	x_tex = (fmod(eve->walls->x_touch[*i], VOLUME) * \
	(eve->map->data.textures.north_texture->width) / VOLUME);
	color = get_pixel(&*eve->map->data.textures.north_texture, x_tex, y_tex);
	mlx_put_pixel(eve->mlx->image, *i, *y, color);
}

void	east(t_eve *eve, int *i, int *y)
{
	uint32_t		color;
	int				y_tex;
	int				x_tex;

	y_tex = ((*y) - (HEIGHT * 0.5) + (eve->walls->walls_height * 0.5)) * \
	eve->map->data.textures.east_texture->height / eve->walls->walls_height;
	x_tex = (fmod(eve->walls->y_touch[*i], VOLUME) * \
	(eve->map->data.textures.east_texture->width) / VOLUME);
	color = get_pixel(&*eve->map->data.textures.east_texture, x_tex, y_tex);
	mlx_put_pixel(eve->mlx->image, *i, *y, color);
}

void	west(t_eve *eve, int *i, int *y)
{
	uint32_t		color;
	int				y_tex;
	int				x_tex;

	y_tex = ((*y) - (HEIGHT * 0.5) + (eve->walls->walls_height * 0.5)) * \
	eve->map->data.textures.west_texture->height / eve->walls->walls_height;
	x_tex = (fmod(eve->walls->y_touch[*i], VOLUME) * \
	(eve->map->data.textures.west_texture->width) / VOLUME);
	color = get_pixel(&*eve->map->data.textures.west_texture, x_tex, y_tex);
	mlx_put_pixel(eve->mlx->image, *i, *y, color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:30 by mlapique          #+#    #+#             */
/*   Updated: 2025/03/21 17:53:31 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_map(t_map *map)
{
	if (map)
	{
		free_tab(map->map_cpy);
		free_tab(map->data.map);
		free(map->north);
		free(map->south);
		free(map->east);
		free(map->west);
		free(map->data.floor);
		free(map->data.ceiling);
		if (map->data.textures.north_texture != NULL)
			mlx_delete_texture(map->data.textures.north_texture);
		if (map->data.textures.south_texture != NULL)
			mlx_delete_texture(map->data.textures.south_texture);
		if (map->data.textures.east_texture != NULL)
			mlx_delete_texture(map->data.textures.east_texture);
		if (map->data.textures.west_texture != NULL)
			mlx_delete_texture(map->data.textures.west_texture);
	}
}

void	free_walls(t_wall *wall)
{
	if (wall)
	{
		if (wall->angle)
			free(wall->angle);
		if (wall->distance)
			free(wall->distance);
		if (wall->draw_function)
			free(wall->draw_function);
		if (wall->north_south)
			free(wall->north_south);
		if (wall->x_touch)
			free(wall->x_touch);
		if (wall->y_touch)
			free(wall->y_touch);
		free(wall);
	}
}

void	free_everything(t_eve *eve)
{
	if (eve)
	{
		free_walls(eve->walls);
		if (eve->mlx)
			free(eve->mlx);
		if (eve->ray)
			free(eve->ray);
		if (eve->pixels)
			free(eve->pixels);
		if (eve->player != NULL)
			free(eve->player);
		free_map(eve->map);
		free(eve->map);
		free(eve);
	}
}

int	ini_eve(t_eve **eve, int argc, char **argv)
{
	*eve = ft_calloc(sizeof(t_eve), 1);
	if (*eve == NULL)
		return (printf("malloc fail\n"), 1);
	ft_bzero((void *)(*eve), sizeof(t_eve));
	(*eve)->e_key_released = true;
	(*eve)->map_key_released = true;
	(*eve)->minimap = false;
	(*eve)->time.new_time = 0;
	(*eve)->time.old_time = 0;
	return (ini_eve_calloc(eve, argc, argv));
}

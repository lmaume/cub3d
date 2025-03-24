/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_struct_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:26 by mlapique          #+#    #+#             */
/*   Updated: 2025/03/21 17:53:28 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/cub3d.h"

int	ini_map(t_map *data_map, int argc, char **argv)
{
	char	**color;

	(void)argc;
	ft_bzero((void *) data_map, sizeof(t_map));
	if (parse_struct(data_map, argv[1]) == 1)
		return (1);
	if (data_map->data.width > 84 || data_map->data.height > 64)
		return (printf("Map too large. (You: y:%d/x:%d\t Max y:84/x:64)\n", \
					data_map->data.width, data_map->data.height), 1);
	color = ft_split(data_map->data.ceiling, ',');
	if (!color)
		return (1);
	data_map->data.color_ceiling = get_color(color);
	free_tab(color);
	color = ft_split(data_map->data.floor, ',');
	if (!color)
		return (1);
	data_map->data.colot_floor = get_color(color);
	free_tab(color);
	return (0);
}

void	ini_player(t_player *player, t_data_map *data)
{
	data->volume = VOLUME;
	player->anglex = 0;
	player->angley = 0;
	if (data->p_side == 'N')
		player->anglez = 3 * (PI / 2);
	else if (data->p_side == 'S')
		player->anglez = PI / 2;
	else if (data->p_side == 'E')
		player->anglez = PI * 2;
	else if (data->p_side == 'W')
		player->anglez = PI;
	player->fov = FOV * PI / 180;
	player->plyr_x = (data->p_x * data->volume) + (data->volume / 2);
	player->plyr_y = (data->p_y * data->volume) + (data->volume / 2);
}

int	ini_wall(t_eve *eve)
{
	ft_bzero((void *) eve->walls, sizeof(t_wall));
	eve->walls->distance = ft_calloc(WIDTH, sizeof(double));
	eve->walls->angle = ft_calloc(WIDTH, sizeof(double));
	eve->walls->north_south = ft_calloc(WIDTH, sizeof(bool));
	eve->walls->draw_function = ft_calloc(4, sizeof(void *));
	eve->walls->x_touch = ft_calloc(WIDTH, sizeof(double));
	eve->walls->y_touch = ft_calloc(WIDTH, sizeof(double));
	if (!eve->walls->distance || !eve->walls->angle || \
		!eve->walls->north_south \
		|| !eve->walls->draw_function || !eve->walls->x_touch \
		|| !eve->walls->y_touch)
		return (1);
	eve->walls->mo_zaik = true;
	eve->walls->nb_wall = 0;
	eve->walls->draw_function[0] = &draw_north_textures;
	eve->walls->draw_function[1] = &draw_south_textures;
	eve->walls->draw_function[2] = &draw_east_textures;
	eve->walls->draw_function[3] = &draw_west_textures;
	return (0);
}

int	ini_eve_calloc(t_eve **eve, int argc, char **argv)
{
	char	**color;

	(*eve)->map = ft_calloc(sizeof(t_map), 1);
	(*eve)->walls = ft_calloc(sizeof(t_wall), 1);
	(*eve)->mlx = ft_calloc(sizeof(t_mlx), 1);
	(*eve)->player = ft_calloc(sizeof(t_player), 1);
	(*eve)->ray = ft_calloc(sizeof(t_ray), 1);
	(*eve)->pixels = ft_calloc(sizeof(uint8_t), \
			WIDTH * HEIGHT * sizeof(uint32_t) + 1);
	if (!(*eve)->map || !(*eve)->walls || !(*eve)->mlx \
	|| !(*eve)->player \
		|| !(*eve)->ray || !(*eve)->pixels)
		return (printf("Malloc error.\n"), 1);
	if (ini_wall(*eve) != 0)
		return (printf("Malloc error.\n"), 1);
	if (ini_map((*eve)->map, argc, argv) != 0)
		return (printf("Struct init error.\n"), 1);
	ini_player((*eve)->player, &(*eve)->map->data);
	return (0);
}

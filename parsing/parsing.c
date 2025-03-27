/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:53:01 by mlapique          #+#    #+#             */
/*   Updated: 2025/03/27 17:59:59 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	is_entry_valid(int argc, char **argv)
{
	int	try;

	if (argv[1] == NULL || argc < 2)
		return (printf("Please select a level.\n"), 1);
	if (ft_strlen(argv[1]) < 5)
		return (printf("Incorrect map name. (ex. 'map.cub'.)\n"), 1);
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
		return (printf("Map extension is not .cub.\n"), 1);
	try = open(argv[1], O_RDONLY);
	if (try == -1)
		return (printf("Map file not found.\n"), 1);
	close(try);
	return (0);
}

static int	floodfill(int x, int y, char **map, t_data_map data)
{
	int	end;

	end = 0;
	if (x + 1 == data.height && ft_strset(map[x], "EWSND0O"))
		return(end++, -1);
	if (map[x][y] == '\0')
		return (end++, -1);
	if (isset(map[x][y], "10DONSEW") == 0)
		return (end++, -1);
	if (isset(map[x][y], "EWSND0O") == 1 && (y == 0 || x == 0))
		return (end++, -1);
	if ((int)ft_strlen(map[x]) - 1 <= y + 1)
		return (end++, -1);
	map[x][y] = '1';
	if (map[x + 1][0] != '\n' && isset(map[x + 1][y], "1\n\0") == 0)
		end += floodfill(x + 1, y, map, data);
	if (x > 0 && map[x - 1][0] != '\n' && isset(map[x - 1][y], "1\n\0") == 0)
		end += floodfill(x - 1, y, map, data);
	if (isset(map[x][y + 1], "1\n\0") == 0)
		end += floodfill(x, y + 1, map, data);
	if (y > 0 && isset(map[x][y - 1], "1\n\0") == 0)
		end += floodfill(x, y - 1, map, data);
	return (end);
}

int	get_next_floor_pos(t_map *data_map)
{
	while (data_map->map_cpy[data_map->last_y] != NULL)
	{
		while (data_map->map_cpy[data_map->last_y][data_map->last_x] != '\0')
		{
			if (isset(data_map->map_cpy[data_map->last_y] \
				[data_map->last_x], "0NSEWDO"))
				return (0);
			data_map->last_x++;
		}
		data_map->last_x = 0;
		data_map->last_y++;
	}
	return (1);
}

int	is_map_surrounded_by_walls(t_map *data_map)
{
	data_map->last_x = 0;
	data_map->last_y = 0;
	while (get_next_floor_pos(data_map) == 0)
		if (floodfill(data_map->last_y, \
						data_map->last_x, data_map->map_cpy, data_map->data) != 0)
			return (1);
	return (0);
}

int	parse_struct(t_map *data, char *filename)
{
	if (init_struct(data, filename) == 1)
		return (1);
	if (player_count(data) != 1)
		return (printf("One player is needed, no more or less.\n"), 1);
	if (is_map_surrounded_by_walls(data) == 1)
		return \
		(printf("Map not surrounded by walls or invalid char in map.\n"), 1);
	return (0);
}

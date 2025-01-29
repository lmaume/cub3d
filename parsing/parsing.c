#include "parsing.h"

void	print_struct(t_map *data_map)
{
	int	i;

	i = 0;
	if (data_map->north != NULL)
		printf("map->north = %s\n", data_map->north);
	if (data_map->south != NULL)
		printf("map->south = %s\n", data_map->south);
	if (data_map->east != NULL)
		printf("map->east = %s\n", data_map->east);
	if (data_map->west != NULL)
		printf("map->west = %s\n", data_map->west);
	if (data_map->data.floor != NULL)
		printf("map->floor = %s\n", data_map->data.floor);
	if (data_map->data.ceiling != NULL)
		printf("map->ceiling = %s\n", data_map->data.ceiling);
	printf("north fd = %d\n", data_map->data.north_fd);
	printf("south fd = %d\n", data_map->data.south_fd);
	printf("east fd = %d\n", data_map->data.east_fd);
	printf("west fd = %d\n", data_map->data.west_fd);
	if (data_map->data.map == NULL)
		return ;
	printf("\n\n");
	while (data_map->data.map[i] != NULL)
	{
		printf("map | %s\n", data_map->data.map[i]);
		i++;
	}
	i = 0;
	if (data_map->map_cpy == NULL)
		return ;
	printf("\n\n");
	while (data_map->map_cpy[i] != NULL)
	{
		printf("copy | %s\n", data_map->map_cpy[i]);
		i++;
	}
}

void	close_textures(t_data_map data_map)
{
	if (data_map.north_fd != -1)
		close(data_map.north_fd);
	if (data_map.south_fd != -1)
		close(data_map.south_fd);
	if (data_map.east_fd != -1)
		close(data_map.east_fd);
	if (data_map.west_fd != -1)
		close(data_map.west_fd);
}

int	is_entry_valid(int argc, char **argv)
{
	if (argv[1] == NULL || ft_strlen(argv[1]) < 5 || argc < 2)
		return (1);
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
		return (printf("Map extension is not .cub.\n"), 1);
	return (0);
}

static int	floodfill(int x, int y, char **map)
{
	int	end;

	end = 0;
	if (isset(map[x][y], "10NSEW") == 0)
		return (printf("Invalid char in map (%c)[%s].\n", map[x][y], map[x]), -1);

	map[x][y] = '1';
	if (isset(map[x + 1][y], "1 \t") == 0)
		end += floodfill(x + 1, y, map);
	if (isset(map[x - 1][y], "1 \t") == 0)
		end += floodfill(x - 1, y, map);
	if (isset(map[x][y + 1], "1 \t") == 0)
		end += floodfill(x, y + 1, map);
	if (isset(map[x][y - 1], "1 \t") == 0)
		end += floodfill(x, y - 1, map);
	else
		end++;
	return (end);
}

int	get_next_floor_pos(t_map *data_map)
{
	while (data_map->map_cpy[data_map->last_y + 1] != NULL)
	{
		while (data_map->map_cpy[data_map->last_y][data_map->last_x] != '\0')
		{
			if (data_map->map_cpy[data_map->last_y][data_map->last_x] == '0')
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
		if (floodfill(data_map->last_y, data_map->last_x, data_map->map_cpy) == 0)
			return (1);
	return (0);
}

int	parse_struct(t_map *data, char *filename)
{
	if (init_struct(data, filename) == 1)
		return (1);
	print_struct(data);
	if (is_map_surrounded_by_walls(data) == 1)
		return (printf("Map not surrounded by walls.\n"), 1);

	return (0);
}

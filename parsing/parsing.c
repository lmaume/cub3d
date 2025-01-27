#include "parsing.h"

int	is_entry_valid(int argc, char **argv)
{
	if (argv[1] == NULL || ft_strlen(argv[1]) < 5 || argc < 2)
		return (1);
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
		return (printf("Map extension is not .cub.\n"), 1);
	return (0);
}

// void	free_map(t_map *data_map)
// {
// 	if (data_map->north != NULL)
// 		free(data_map->north);
// 	if (data_map->south != NULL)
// 		free(data_map->south);
// 	if (data_map->east != NULL)
// 		free(data_map->east);
// 	if (data_map->west != NULL)
// 		free(data_map->west);
// 	if (data_map->floor != NULL)
// 		free(data_map->floor);
// 	if (data_map->ceiling != NULL)
// 		free(data_map->ceiling);
// }

int	parse_struct(t_map *data, char *filename)
{
	if (init_struct(data, filename) == 1)
		return (1);
	return (0);
}

#include "parsing.h"

void	print_struct(t_map *data_map)
{
	//? cardinal directions
	if (data_map->north != NULL)
		printf("map->north = %s\n", data_map->north);
	if (data_map->south != NULL)
		printf("map->south = %s\n", data_map->south);
	if (data_map->east != NULL)
		printf("map->east = %s\n", data_map->east);
	if (data_map->west != NULL)
		printf("map->west = %s\n", data_map->west);
	//? floor & ceiling
	if (data_map->data.floor != NULL)
		printf("map->floor = %s\n", data_map->data.floor);
	if (data_map->data.ceiling != NULL)
		printf("map->ceiling = %s\n", data_map->data.ceiling);
	//? cardinal fds
	printf("north fd = %d\n", data_map->data.north_fd);
	printf("south fd = %d\n", data_map->data.south_fd);
	printf("east fd = %d\n", data_map->data.east_fd);
	printf("west fd = %d\n", data_map->data.west_fd);
}

int	init_var(char **tab, char **str, char *opt)
{
	char	*tmp;

	tmp = NULL;
	if (ft_tabcmp(tab, opt) != NULL)
		tmp = &ft_tabcmp(tab, opt)[ft_strlen(opt)];
	// if (tmp == NULL)
	// 	tmp = &ft_tabchr(tab, opt[0])[ft_strlen(opt) - 1];
	if (tmp == NULL)
		return (printf("One or more identifier is not reconized.\n"), 1);
	tmp[ft_strlen(tmp) - 1] = '\0';
	*str = tmp;
	return (0);
}

int	open_texture(t_map *data_map)
{
	data_map->data.north_fd = open(data_map->north, O_RDONLY);
	if (data_map->data.north_fd < 0)
		return (1);
	data_map->data.south_fd = open(data_map->south, O_RDONLY);
	if (data_map->data.south_fd < 0)
		return (1);
	data_map->data.east_fd = open(data_map->east, O_RDONLY);
	if (data_map->data.east_fd < 0)
		return (1);
	data_map->data.west_fd = open(data_map->west, O_RDONLY);
	if (data_map->data.west_fd < 0)
		return (1);
	return (0);
}

int	init_struct(t_map *data_map, char *filename)
{
	char	**tab;

	tab = ft_file_to_tab(filename);
	if (init_var(tab, &data_map->north, "NO ") == 1)
		return (1);
	if (init_var(tab, &data_map->south, "SO ") == 1)
		return (1);
	if (init_var(tab, &data_map->east, "EA ") == 1)
		return (1);
	if (init_var(tab, &data_map->west, "WE ") == 1)
		return (1);
	if (init_var(tab, &data_map->data.floor, "F ") == 1)
		return (1);
	if (init_var(tab, &data_map->data.ceiling, "C ") == 1)
		return (1);
	if (data_map->data.floor == NULL || data_map->data.ceiling == NULL)
		return (1);
	open_texture(data_map);
	print_struct(data_map);
	free(tab);
	return (0);
}

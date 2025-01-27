#include "parsing.h"

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

int	init_var(char **tab, char **str, char *opt)
{
	char	*tmp;

	tmp = NULL;
	if (ft_tabcmp(tab, opt) != NULL)
		tmp = &ft_tabcmp(tab, opt)[ft_strlen(opt)];
	if (tmp == NULL)
		return (printf("One or more identifier is not reconized.\n"), 1);
	tmp[ft_strlen(tmp) - 1] = '\0';
	*str = tmp;
	return (0);
}

int	get_map_line(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i] != NULL)
	{
		while (ft_iswhite_space(tab[i][j]) == 1)
			j++;
		if (isset(tab[i][j], "10") == 1)
			return (i);
		j = 0;
		i++;
	}
	return (0);
}

int	init_struct(t_map *data_map, char *filename)
{
	char	**tab;

	tab = ft_file_to_tab(filename);
	if (init_var(tab, &data_map->north, "NO ") == 1)
		return (free(tab), 1);
	if (init_var(tab, &data_map->south, "SO ") == 1)
		return (free(tab), 1);
	if (init_var(tab, &data_map->east, "EA ") == 1)
		return (free(tab), 1);
	if (init_var(tab, &data_map->west, "WE ") == 1)
		return (free(tab), 1);
	if (init_var(tab, &data_map->data.floor, "F ") == 1)
		return (free(tab), 1);
	if (init_var(tab, &data_map->data.ceiling, "C ") == 1)
		return (free(tab), 1);
	if (data_map->data.floor == NULL || data_map->data.ceiling == NULL)
		return (free(tab), 1);
	data_map->data.map = &tab[get_map_line(tab)];
	if (data_map->data.map == 0)
		return (free(tab), 1);
	open_texture(data_map);
	print_struct(data_map);
	free(tab);
	return (0);
}

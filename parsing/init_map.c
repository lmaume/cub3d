#include "parsing.h"

//TODO CHANGER POUR RENDRE COMPATIBLE AVEC LA MLX
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
		return (printf("One or more identifier is not recoGnized.\n"), 1);
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

int	map_alloc(t_map *data_map, char ***tab)
{
	data_map->data.map = ft_calloc(sizeof(char **), 1);
	data_map->map_cpy = ft_calloc(sizeof(char **), 1);
	data_map->data.map = &(*tab)[get_map_line(*tab)];
	data_map->map_cpy = &(*tab)[get_map_line(*tab)];
	if (data_map->data.map == NULL || data_map->map_cpy == NULL)
		return (free(*tab), 1);
	return (0);
}

int	init_struct(t_map *data_map, char *filename)
{
	char	**tab;

	tab = ft_file_to_tab(filename);
	if (tab == NULL)
		return (printf("File '%s' not found.\n", filename), 1);
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
	if (map_alloc(data_map, &tab) == 1)
		return (1);
	if (open_texture(data_map) == 1)
		return (printf("One or more file not found.\n"), 1);
	free(tab);
	return (0);
}

#include "parsing.h"

int	init_var(char **tab, char *str, char *opt)
{
	char	*tmp;

	tmp = ft_tabcmp(tab, opt);
	if (tmp == NULL)
		tmp = ft_tabchr(tab, "N");
	if (tmp == NULL)
		return (1);
	str = tmp;
	return (0);
}

int	init_struct(t_map *data_map, char *filename)
{
	char	**tab;

	tab = ft_file_to_tab(filename);
	if (init_var(tab, data_map->north, "NO ") == 1)
		return (1);
	if (init_var(tab, data_map->south, "SO ") == 1)
		return (1);
	if (init_var(tab, data_map->east, "EA ") == 1)
		return (1);
	if (init_var(tab, data_map->west, "WE ") == 1)
		return (1);
	data_map->floor = ft_tabchr(tab, "F");
	data_map->ceiling = ft_tabchr(tab, "C");
	if (data_map->floor == NULL || data_map->ceiling == NULL)
		return (1);
	free(tab);
	return (0);
}

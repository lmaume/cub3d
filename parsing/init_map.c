#include "../include/parsing.h"

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

static int	init_var(char **tab, char **str, char *opt)
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

int	player_count(t_map *data_map)
{
	int	player_count;
	int	i;
	int	j;

	j = 0;
	i = 0;
	player_count = 0;
	while (data_map->map_cpy[i] != NULL)
	{
		while (data_map->map_cpy[i][j] != '\0')
		{
			if (isset(data_map->map_cpy[i][j], "NSEW") == 1)
			{
				data_map->data.p_x = j;
				data_map->data.p_y = i;
				data_map->data.p_side = data_map->map_cpy[i][j];
				player_count++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (player_count);
}

int	init_struct(t_map *data_map, char *filename)
{
	char	**tab;

	tab = ft_file_to_tab(filename);
	if (tab == NULL)
		return (printf("File '%s' not found.\n", filename), 1);
	if (init_var(tab, &data_map->north, "NO ") == 1)
		return (free_tab(tab), 1);
	if (init_var(tab, &data_map->south, "SO ") == 1)
		return (free_tab(tab), 1);
	if (init_var(tab, &data_map->east, "EA ") == 1)
		return (free_tab(tab), 1);
	if (init_var(tab, &data_map->west, "WE ") == 1)
		return (free_tab(tab), 1);
	if (init_var(tab, &data_map->data.floor, "F ") == 1)
		return (free_tab(tab), 1);
	if (init_var(tab, &data_map->data.ceiling, "C ") == 1)
		return (free_tab(tab), 1);
	if (data_map->data.floor == NULL || data_map->data.ceiling == NULL)
		return (free_tab(tab), 1);
	if (map_alloc(data_map, tab) == 1)
		return (free_tab(tab), 1);
	if (open_texture(data_map) == 1)
		return (printf("One or more file not found.\n"), free_tab(tab), 1);
	free_tab(tab);
	return (0);
}

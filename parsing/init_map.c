#include "../include/cub3d.h"

int	open_texture(t_map *data_map)
{
	t_textures *north_texture;
	t_textures *south_texture;
	t_textures *east_texture;
	t_textures *west_texture;
	north_texture = mlx_load_png(data_map->north);
	south_texture = mlx_load_png(data_map->south);
	east_texture = mlx_load_png(data_map->east);
	west_texture = mlx_load_png(data_map->west);
    if (north_texture == NULL || south_texture == NULL \
			|| east_texture == NULL || west_texture == NULL)
        return (1);
	data_map->data.textures.north_image = mlx_texture_to_image(data_map->eve->mlx->mlx, north_texture);
	if (data_map->data.textures.north_image == NULL)
		return (1);
	data_map->data.textures.south_image = mlx_texture_to_image(data_map->eve->mlx->mlx, south_texture);
	if (data_map->data.textures.south_image == NULL)
		return (1);
	data_map->data.textures.east_image = mlx_texture_to_image(data_map->eve->mlx->mlx, east_texture);
	if (data_map->data.textures.east_image == NULL)
		return (1);
	data_map->data.textures.west_image = mlx_texture_to_image(data_map->eve->mlx->mlx, west_texture);
	if (data_map->data.textures.west_image == NULL)
		return (1);
	
	return (0);
}

void	close_images(t_map *data_map)
{
	if (data_map->data.textures.north_image != NULL)
		mlx_delete_image(data_map->eve->mlx->mlx, data_map->data.textures.north_image);
	if (data_map->data.textures.south_image != NULL)
		mlx_delete_image(data_map->eve->mlx->mlx, data_map->data.textures.south_image);
	if (data_map->data.textures.east_image != NULL)
		mlx_delete_image(data_map->eve->mlx->mlx, data_map->data.textures.east_image);
	if (data_map->data.textures.west_image != NULL)
		mlx_delete_image(data_map->eve->mlx->mlx, data_map->data.textures.west_image);
}

static int	init_var(char **tab, char **str, char *opt)
{
	char	*tmp;

	tmp = NULL;
	if (ft_tabcmp(tab, opt) != NULL)
		tmp = &ft_tabcmp(tab, opt)[ft_strlen(opt)];
	if (tmp == NULL)
		return (printf("One or more identifier is not recognized.\n"), 1);
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
	if (tab == NULL || tab[0] == NULL)
		return (printf("Incorrect or empty file.\n"), free(tab), 1);
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

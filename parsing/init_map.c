#include "../include/cub3d.h"

static void	close_images(t_eve *eve)
{
	if (!eve->map->data.textures.north_image || \
		!eve->map->data.textures.south_image || \
		!eve->map->data.textures.east_image || \
		!eve->map->data.textures.west_image)
		printf("Texture to Image fail.\n");
}

int	open_texture(t_eve *eve)
{
	mlx_texture_t *north_texture;
	mlx_texture_t *south_texture;
	mlx_texture_t *east_texture;
	mlx_texture_t *west_texture;
	if (!eve || !eve->mlx || !eve->mlx->mlx)
		return (printf("MLX load fail.\n"), 1);
	north_texture = mlx_load_png(eve->map->north);
	south_texture = mlx_load_png(eve->map->south);
	east_texture = mlx_load_png(eve->map->east);
	west_texture = mlx_load_png(eve->map->west);
	if (!north_texture || !south_texture || !east_texture || !west_texture)
		return (printf("Texture load fail.\n"), 1);
	eve->map->data.textures.north_image = mlx_texture_to_image(eve->mlx->mlx, north_texture);
	eve->map->data.textures.south_image = mlx_texture_to_image(eve->mlx->mlx, south_texture);
	eve->map->data.textures.east_image = mlx_texture_to_image(eve->mlx->mlx, east_texture);
	eve->map->data.textures.west_image = mlx_texture_to_image(eve->mlx->mlx, west_texture);
	close_images(eve);
	mlx_delete_texture(north_texture);
	mlx_delete_texture(south_texture);
	mlx_delete_texture(east_texture);
	mlx_delete_texture(west_texture);
	return (0);
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
	*str = ft_calloc(sizeof(char *), ft_strlen(tmp));
	ft_memcpy(*str, tmp, ft_strlen(tmp) + 1);
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
	data_map->data.file_content = tab;
	free_tab(tab);
	return (0);
}

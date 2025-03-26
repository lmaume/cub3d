/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:52:58 by mlapique          #+#    #+#             */
/*   Updated: 2025/03/26 16:46:32 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!eve || !eve->mlx || !eve->mlx->mlx)
		return (printf("MLX load fail.\n"), 1);
	eve->map->data.textures.north_texture = mlx_load_png(eve->map->north);
	eve->map->data.textures.south_texture = mlx_load_png(eve->map->south);
	eve->map->data.textures.east_texture = mlx_load_png(eve->map->east);
	eve->map->data.textures.west_texture = mlx_load_png(eve->map->west);
	if (!eve->map->data.textures.north_texture || \
		!eve->map->data.textures.south_texture || \
		!eve->map->data.textures.east_texture || \
		!eve->map->data.textures.west_texture)
		return (printf("Texture load fail.\n"), 1);
	eve->map->data.textures.north_image = mlx_texture_to_image(eve->mlx->mlx, \
		eve->map->data.textures.north_texture);
	eve->map->data.textures.south_image = mlx_texture_to_image(eve->mlx->mlx, \
		eve->map->data.textures.south_texture);
	eve->map->data.textures.east_image = mlx_texture_to_image(eve->mlx->mlx, \
		eve->map->data.textures.east_texture);
	eve->map->data.textures.west_image = mlx_texture_to_image(eve->mlx->mlx, \
		eve->map->data.textures.west_texture);
	close_images(eve);
	return (0);
}

static int	init_var(char **tab, char **str, char *opt)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (ft_tabcmp(tab, opt) != NULL)
		tmp = &ft_tabcmp(tab, opt)[ft_strlen(opt)];
	if (tmp == NULL)
		return (printf("One or more identifier is not recognized.\n"), 1);
	while (ft_strncmp(tab[i], opt, ft_strlen(opt)) != 0)
		i++;
	if (i > get_map_line(tab))
		return (printf("Identifier after map or inside the map wtf.\n"), 1);
	tmp[ft_strlen(tmp) - 1] = '\0';
	*str = ft_calloc(sizeof(char *), ft_strlen(tmp));
	if (!*str)
		return (1);
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

#include "../include/cub3d.h"

void	free_everything(t_eve *eve)
{
	free_tab(eve->map->map_cpy);
	free_tab(eve->map->data.map);
	free(eve->map->north);
	free(eve->map->south);
	free(eve->map->east);
	free(eve->map->west);
	free(eve->map->data.floor);
	free(eve->map->data.ceiling);
	free(eve);
	free(eve->mlx);
	if (eve->player != NULL)
		free(eve->player);
	free(eve->ray);
	free(eve->pixels);
	free(eve->map);
	free(eve->walls->distance);
	free(eve->walls->x_tab);
	free(eve->p2);
	free(eve->walls->wall_x);
	free(eve->walls->wall_y);
	free(eve->walls->ray_x);
	free(eve->walls->ray_y);
	free(eve->walls);
	if (eve->map->data.textures.north_texture != NULL)
	{
		mlx_delete_texture(eve->map->data.textures.north_texture);
		mlx_delete_texture(eve->map->data.textures.south_texture);
		mlx_delete_texture(eve->map->data.textures.east_texture);
		mlx_delete_texture(eve->map->data.textures.west_texture);
	}
}

int	ini_map(t_map *data_map, char **argv)
{
	if (parse_struct(data_map, argv[1]) == 1)
		return (1);
	if (data_map->data.width > 128 || data_map->data.height > 128)
		return (printf("Map too large. (%d/%d, max 128)\n", \
					data_map->data.width, data_map->data.height), 1);
	return (0);
}

void	ini_player(t_player *player, t_data_map *data)
{
	data->volume = get_volume(data->height, data->width);
	player->anglex = 0;
	player->angley = 0;
	if (data->p_side == 'N')
		player->anglez = 3 * (M_PI / 2);
	else if (data->p_side == 'S')
		player->anglez = M_PI / 2;
	else if (data->p_side == 'E')
		player->anglez = M_PI * 2;
	else if (data->p_side == 'W')
		player->anglez = M_PI;
	player->fov = FOV;
	// printf("%d\n", data->volume);
	player->plyr_x = (data->p_x * data->volume) + (data->volume / 2);
	player->plyr_y = (data->p_y * data->volume) + (data->volume / 2);
}

int	ini_eve(t_eve **eve, char **argv)
{
	*eve = ft_calloc(sizeof(t_eve), 1);
	(*eve)->map = ft_calloc(sizeof(t_map), 1);
	(*eve)->mlx = ft_calloc(sizeof(t_mlx), 1);
	(*eve)->player = ft_calloc(sizeof(t_player), 1);
	(*eve)->ray = ft_calloc(sizeof(t_ray), 1);
	(*eve)->pixels = ft_calloc(sizeof(uint8_t), \
			WIDTH * HEIGHT * sizeof(uint32_t) + 1);
	(*eve)->e_key_released = true;
	if (ini_map((*eve)->map, argv) != 0)
		return (printf("Struct init error.\n"), 1);
	ini_player((*eve)->player, &(*eve)->map->data);
	(*eve)->walls = ft_calloc(sizeof(t_wall), 1);
	(*eve)->walls->wall_x = ft_calloc(sizeof(int *), 2048 + 1);
	(*eve)->walls->wall_y = ft_calloc(sizeof(int *), 2048 + 1);
	(*eve)->walls->ray_x = ft_calloc(sizeof(int *), 2048 + 1);
	(*eve)->walls->ray_y = ft_calloc(sizeof(int *), 2048 + 1);
	(*eve)->walls->nb_wall = 0;
	(*eve)->p2 = ft_calloc(sizeof(t_point), 2048 + 1);
	(*eve)->walls->distance = ft_calloc(2048 + 1, sizeof(double));
	(*eve)->walls->x_tab = ft_calloc(2048, sizeof(double));
	return (0);

}

void	my_mlx_pixel_put(mlx_image_t *image, int x, int y, uint32_t color)
{
	uint8_t	*pixelstart;
	int	test;
	
	test = (y * image->width + x) * 4;
	if (test > 0 && test < HEIGHT * WIDTH * 4)
	{
		pixelstart = &image->pixels[test];
		*(pixelstart++) = color >> 24;
		*(pixelstart++) = color >> 16;
		*(pixelstart++) = color >> 8;
		*(pixelstart) = color;
	}
}

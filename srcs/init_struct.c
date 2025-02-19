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
	if (eve->map->data.textures.north_texture != NULL)
	{
		mlx_delete_texture(eve->map->data.textures.north_texture);
		mlx_delete_texture(eve->map->data.textures.south_texture);
		mlx_delete_texture(eve->map->data.textures.east_texture);
		mlx_delete_texture(eve->map->data.textures.west_texture);
	}
}

int	ini_map(t_map *data_map, int argc, char **argv)
{
	(void)argc;
	if (parse_struct(data_map, argv[1]) == 1)
		return (1);
	if (data_map->data.width > 128 || data_map->data.height > 128)
		return (printf("Map too large. (%d/%d, max 128)\n", \
					data_map->data.width, data_map->data.height), 1);
	return (0);
}

void	ini_player(t_player *player, t_data_map *data)
{
	data->volume = 48;
	player->anglex = 0;
	player->angley = 0;
	if (data->p_side == 'N')
		player->anglez = 3 * (PI / 2);
	else if (data->p_side == 'S')
		player->anglez = PI / 2;
	else if (data->p_side == 'E')
		player->anglez = PI * 2;
	else if (data->p_side == 'W')
		player->anglez = PI;
	player->fov = FOV;
	player->plyr_x = (data->p_x * data->volume) + (data->volume / 2);
	player->plyr_y = (data->p_y * data->volume) + (data->volume / 2);
}

int	ini_eve(t_eve **eve, int argc, char **argv)
{
	*eve = ft_calloc(sizeof(t_eve), 1);
	(*eve)->map = ft_calloc(sizeof(t_map), 1);
	(*eve)->mlx = ft_calloc(sizeof(t_mlx), 1);
	(*eve)->player = ft_calloc(sizeof(t_player), 1);
	(*eve)->ray = ft_calloc(sizeof(t_ray), 1);
	(*eve)->pixels = ft_calloc(sizeof(uint8_t), \
			WIDTH * HEIGHT * sizeof(uint32_t) + 1);
	(*eve)->e_key_released = true;
	if (ini_map((*eve)->map, argc, argv) != 0)
		return (printf("Struct init error.\n"), 1);
	ini_player((*eve)->player, &(*eve)->map->data);
	(void)argc;
	(void)argv;
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

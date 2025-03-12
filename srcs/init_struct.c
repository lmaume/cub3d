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
	free(eve->mlx);
	if (eve->player != NULL)
		free(eve->player);
	free(eve->ray);
	free(eve->pixels);
	if (eve->map->data.textures.north_texture != NULL)
		mlx_delete_texture(eve->map->data.textures.north_texture);
	if (eve->map->data.textures.south_texture != NULL)
		mlx_delete_texture(eve->map->data.textures.south_texture);
	if (eve->map->data.textures.east_texture != NULL)
		mlx_delete_texture(eve->map->data.textures.east_texture);
	if (eve->map->data.textures.west_texture != NULL)
		mlx_delete_texture(eve->map->data.textures.west_texture);
	free(eve->map);
	free_game(eve->walls);
	free(eve);
}

int	ini_map(t_map *data_map, int argc, char **argv)
{
	(void)argc;
	if (parse_struct(data_map, argv[1]) == 1)
		return (1);
	if (data_map->data.width > 84 || data_map->data.height > 64)
		return (printf("Map too large. (%d/%d, max 84/64)\n", \
					data_map->data.width, data_map->data.height), 1);
	return (0);
}

void	ini_player(t_player *player, t_data_map *data)
{
	data->volume = VOLUME;
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
	player->fov = FOV * PI / 180;
	player->plyr_x = (data->p_x * data->volume) + (data->volume / 2);
	player->plyr_y = (data->p_y * data->volume) + (data->volume / 2);
}

void	ini_wall(t_eve *eve)
{
	eve->walls = ft_calloc(sizeof(t_wall), 1);
	eve->walls->nb_wall = 0;
	eve->walls->distance = ft_calloc(WIDTH, sizeof(double));
	eve->walls->angle = ft_calloc(WIDTH, sizeof(double));
	eve->walls->north_south = ft_calloc(WIDTH, sizeof(bool));
	eve->walls->draw_function = ft_calloc(4, sizeof(void *));
	eve->walls->draw_function[0] = &draw_north_textures;
	eve->walls->draw_function[1] = &draw_south_textures;
	eve->walls->draw_function[2] = &draw_east_textures;
	eve->walls->draw_function[3] = &draw_west_textures;
	eve->walls->x_touch = ft_calloc(WIDTH, sizeof(double));
	eve->walls->y_touch = ft_calloc(WIDTH, sizeof(double));
	eve->walls->mo_zaik = true;
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
	(*eve)->map_key_released = true;
	(*eve)->minimap = false;
	ini_wall(*eve);
	(*eve)->time.new_time = 0;
	(*eve)->time.old_time = 0;
	if (ini_map((*eve)->map, argc, argv) != 0)
		return (printf("Struct init error.\n"), 1);
	ini_player((*eve)->player, &(*eve)->map->data);
	return (0);
}

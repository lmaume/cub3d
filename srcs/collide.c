#include "../include/cub3d.h"

static void get_forward_tile(int *tile_x, int *tile_y, t_eve *eve, double distance)
{
	int	volume;

	volume = get_volume(eve->map->data.height, eve->map->data.width);
	*tile_x = (eve->player->plyr_x + cos(eve->player->anglez) * distance) / volume;
	*tile_y = (eve->player->plyr_y + sin(eve->player->anglez) * distance) / volume;
}

void open_door(t_eve *eve)
{
	int	volume;
	int	tile_x;
	int	tile_y;

	volume = get_volume(eve->map->data.height, eve->map->data.width);
	get_forward_tile(&tile_x, &tile_y, eve->player, volume);
	if (eve->map->data.map[tile_y][tile_x] == 'D' && mlx_is_key_down(eve->mlx->mlx, MLX_KEY_E))
		eve->map->data.map[tile_y][tile_x] = 'O';
	if (eve->map->data.map[tile_y][tile_x] == 'O' && mlx_is_key_down(eve->mlx->mlx, MLX_KEY_E))
		eve->map->data.map[tile_y][tile_x] = 'D';
}

bool	is_player_near_door(t_data_map *data, int x, int y)
{
	int	volume;

	volume = get_volume(data->height, data->width);
	if (isset(data->map[y / volume][x / volume], "DO") == 1)
		return (true);
	return (false);
}

//? la hitbox est sur le centre du personnage, pas sur les bords. est-ce un probleme ? pas pour l'instant. ?//
bool	is_player_in_wall(t_data_map *data, int x, int y)
{
	int	volume;

	volume = get_volume(data->height, data->width);
	if (isset(data->map[y / volume][x / volume], "1D") == 1)
		return (true);
	return (false);
}

#include "../include/cub3d.h"

static void	move_up(t_eve *eve, int speed)
{
	if (is_player_in_wall(&eve->map->data, eve->player->plyr_x + cos(eve->player->player_orientation) * speed, eve->player->plyr_y) == false)
		eve->player->plyr_x += cos(eve->player->player_orientation) * speed;
	if (is_player_in_wall(&eve->map->data, eve->player->plyr_x, eve->player->plyr_y - sin(eve->player->player_orientation) * speed) == false)
		eve->player->plyr_y -= sin(eve->player->player_orientation) * speed;
}

static void	move_down(t_eve *eve)
{
	if (is_player_in_wall(&eve->map->data, eve->player->plyr_x - cos(eve->player->player_orientation) * 5, eve->player->plyr_y) == false)
		eve->player->plyr_x -= cos(eve->player->player_orientation) * 5;
	if (is_player_in_wall(&eve->map->data, eve->player->plyr_x, eve->player->plyr_y + sin(eve->player->player_orientation) * 5) == false)
		eve->player->plyr_y += sin(eve->player->player_orientation) * 5;
}

static void	move_left(t_eve *eve, int speed)
{
	if (is_player_in_wall(&eve->map->data, eve->player->plyr_x + cos(eve->player->player_orientation + PI / 2) * speed, eve->player->plyr_y) == false)
		eve->player->plyr_x += cos(eve->player->player_orientation + PI / 2) * speed;
	if (is_player_in_wall(&eve->map->data, eve->player->plyr_x, eve->player->plyr_y - sin(eve->player->player_orientation + PI / 2) * speed) == false)
		eve->player->plyr_y -= sin(eve->player->player_orientation + PI / 2) * speed;
}

static void	move_right(t_eve *eve, int speed)
{
	if (is_player_in_wall(&eve->map->data, eve->player->plyr_x - cos(eve->player->player_orientation + PI / 2) * speed, eve->player->plyr_y) == false)
		eve->player->plyr_x -= cos(eve->player->player_orientation + PI / 2) * speed;
	if (is_player_in_wall(&eve->map->data, eve->player->plyr_x, eve->player->plyr_y + sin(eve->player->player_orientation + PI / 2) * speed) == false)
		eve->player->plyr_y += sin(eve->player->player_orientation + PI / 2) * speed;
}

void	ft_move(t_eve *eve)
{
	int		shift;
	int		speed;

	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_LEFT_SHIFT))
		shift = 2;
	else
		shift = 1;
	speed = (5 * shift);
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_W))
		move_up(eve, speed);
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_S))
		move_down(eve);
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_A))
		move_left(eve, speed);
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_D))
		move_right(eve, speed);
}

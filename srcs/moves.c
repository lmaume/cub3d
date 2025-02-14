#include "../include/cub3d.h"

static void	move_forward(t_eve *eve, int speed)
{
	printf("angle z = %f\n", eve->player->anglez);
	if (is_player_in_wall(&eve->map->data, eve->player->plyr_x + cos(eve->player->anglez) * (speed * 2), eve->player->plyr_y) == false)
		eve->player->plyr_x += cos(eve->player->anglez) * speed;
	if (is_player_in_wall(&eve->map->data, eve->player->plyr_x, eve->player->plyr_y + sin(eve->player->anglez) * (speed * 2)) == false)
		eve->player->plyr_y += sin(eve->player->anglez) * speed;
}

static void	move_backward(t_eve *eve)
{
	printf("angle z = %f\n", eve->player->anglez);
	if (is_player_in_wall(&eve->map->data, eve->player->plyr_x - cos(eve->player->anglez) * 10, eve->player->plyr_y) == false)
		eve->player->plyr_x -= cos(eve->player->anglez) * 5;
	if (is_player_in_wall(&eve->map->data, eve->player->plyr_x, eve->player->plyr_y - sin(eve->player->anglez) * 10) == false)
		eve->player->plyr_y -= sin(eve->player->anglez) * 5;
}

static void	move_left(t_eve *eve)
{
	printf("angle z = %f\n", eve->player->anglez);
	if (is_player_in_wall(&eve->map->data, eve->player->plyr_x - cos(eve->player->anglez + PI / 2) * 10, eve->player->plyr_y) == false)
		eve->player->plyr_x -= cos(eve->player->anglez + PI / 2) * 5;
	if (is_player_in_wall(&eve->map->data, eve->player->plyr_x, eve->player->plyr_y - sin(eve->player->anglez + PI / 2) * 10) == false)
		eve->player->plyr_y -= sin(eve->player->anglez + PI / 2) * 5;
}

static void	move_right(t_eve *eve)
{
	printf("angle z = %f\n", eve->player->anglez);
	if (is_player_in_wall(&eve->map->data, eve->player->plyr_x + cos(eve->player->anglez + PI / 2) * 10, eve->player->plyr_y) == false)
		eve->player->plyr_x += cos(eve->player->anglez + PI / 2) * 5;
	if (is_player_in_wall(&eve->map->data, eve->player->plyr_x, eve->player->plyr_y + sin(eve->player->anglez + PI / 2) * 10) == false)
		eve->player->plyr_y += sin(eve->player->anglez + PI / 2) * 5;
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
		move_forward(eve, speed);
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_S))
		move_backward(eve);
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_A))
		move_left(eve);
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_D))
		move_right(eve);
}

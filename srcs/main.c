#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/cub3d.h"

// -----------------------------------------------------------------------------

static void	ft_hook(void *param)
{
	t_eve	*eve;

	eve = param;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(eve->mlx->mlx);
	ft_move(eve);
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_LEFT))
		eve->player->anglez -= 0.06;
	if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_RIGHT))
		eve->player->anglez += 0.06;
	if (eve->player->anglez > 2 * PI)
		eve->player->anglez -= 2 * PI;
	if (eve->player->anglez < 0)
		eve->player->anglez += 2 * PI;
	open_door(eve);
}

static void	game_loop(void *ev)
{
	t_eve	*eve;

	eve = ev;
	mlx_delete_image(eve->mlx->mlx, eve->mlx->image);
	eve->mlx->image = mlx_new_image(eve->mlx->mlx, WIDTH, HEIGHT);
	game(eve);
	mlx_image_to_window(eve->mlx->mlx, eve->mlx->image, 0, 0);
}

static void	game_start(t_eve *eve)
{
	mlx_loop_hook(eve->mlx->mlx, game_loop, eve);
	mlx_loop_hook(eve->mlx->mlx, ft_hook, eve);
	mlx_loop_hook(eve->mlx->mlx, mouse_move, eve);
	mlx_loop(eve->mlx->mlx);
}

static int	mlx_start(t_eve *eve)
{
	eve->mlx->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	eve->mlx->image = mlx_new_image(eve->mlx->mlx, HEIGHT, WIDTH);
	if (eve->mlx->mlx == NULL)
	{
		puts(mlx_strerror(mlx_errno));
		return (free_everything(eve), EXIT_FAILURE);
	}
	if (open_texture(eve) == 1)
		return (printf("One or more file not found.\n"), \
									free_everything(eve), 1);
	if (eve->mlx->image == NULL)
	{
		mlx_close_window(eve->mlx->mlx);
		puts(mlx_strerror(mlx_errno));
		return (free_everything(eve), EXIT_FAILURE);
	}
	if (mlx_image_to_window(eve->mlx->mlx, eve->mlx->image, 0, 0) == -1)
	{
		mlx_close_window(eve->mlx->mlx);
		puts(mlx_strerror(mlx_errno));
		return (free_everything(eve), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
// -----------------------------------------------------------------------------

int32_t	main(int argc, char **argv)
{
	t_eve	*eve;

	eve = NULL;
	if (is_entry_valid(argc, argv) != 0)
		return (EXIT_FAILURE);
	if (ini_eve(&eve, argc, argv) != 0)
		return (free_everything(eve), EXIT_FAILURE);
	if (mlx_start(eve) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	game_start(eve);
	mlx_terminate(eve->mlx->mlx);
	free_everything(eve);
	return (EXIT_SUCCESS);
}

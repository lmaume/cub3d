#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/cub3d.h"

// -----------------------------------------------------------------------------

void	mouse_move(void *param)
{
	static int	old_x = INT8_MIN;
	int			x;
	int			y;
	double		new_angle;
	t_eve		*eve;

	eve = param;
	mlx_set_cursor_mode(eve->mlx->mlx, MLX_MOUSE_DISABLED);
	mlx_get_mouse_pos(eve->mlx->mlx, &x, &y);
	new_angle = ((double)(x - old_x) / WIDTH) * (2 * PI);
	if (old_x == INT8_MIN)
	{
		old_x = x;
		return ;
	}
	old_x = x;
	eve->player->anglez += (new_angle);
}

void	ft_hook(void *param)
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
	open_door(eve);
	// if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_UP))
	// 	eve->player->angley += 0.05;
	// if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_DOWN))
	// 	eve->player->angley -= 0.05;
	// if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_L))
	// 	eve->player->anglex += 0.05;
	// if (mlx_is_key_down(eve->mlx->mlx, MLX_KEY_K))
	// 	eve->player->anglex -= 0.05;
}

void	game_loop(void *ev)
{
	t_eve *eve;

	eve = ev;
	mlx_delete_image(eve->mlx->mlx, eve->mlx->image);
	eve->mlx->image = mlx_new_image(eve->mlx->mlx, WIDTH, HEIGHT);
	game(eve);
	mlx_image_to_window(eve->mlx->mlx, eve->mlx->image, 0, 0);
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
	if (!(eve->mlx->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(free_everything(eve), EXIT_FAILURE);
	}
	if (open_texture(eve) == 1)
		return (printf("One or more file not found.\n"), free_everything(eve), 1);
	if (!(eve->mlx->image = mlx_new_image(eve->mlx->mlx, HEIGHT, WIDTH)))
	{
		mlx_close_window(eve->mlx->mlx);
		puts(mlx_strerror(mlx_errno));
		return(free_everything(eve), EXIT_FAILURE);
	}
	if (mlx_image_to_window(eve->mlx->mlx, eve->mlx->image, 0, 0) == -1)
	{
		mlx_close_window(eve->mlx->mlx);
		puts(mlx_strerror(mlx_errno));
		return(free_everything(eve), EXIT_FAILURE);
	}
	mlx_loop_hook(eve->mlx->mlx, game_loop, eve);
	mlx_loop_hook(eve->mlx->mlx, ft_hook, eve);
	mlx_loop_hook(eve->mlx->mlx, mouse_move, eve);
	mlx_loop(eve->mlx->mlx);
	mlx_terminate(eve->mlx->mlx);
	free_everything(eve);
	return (EXIT_SUCCESS);
}


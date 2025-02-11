#include "../include/cub3d.h"

void	draw_wall(t_eve *eve, mlx_image_t *image, double distance)
{
	double				wall_height;
	int					y_start;
	int					y_end;
	t_line_necessary	*draw_line;

	draw_line = ft_calloc(sizeof(t_line_necessary), 1);
	wall_height = (HEIGHT * 30) / distance;
	y_start = (HEIGHT / 2) - (wall_height / 2);
	y_end = (HEIGHT / 2) + (wall_height / 2);
	int y = y_start;
	while (y < y_end)
	{
		line(draw_line, image);
		y++;
	}
	free(draw_line);
}

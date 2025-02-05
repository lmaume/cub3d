#include "../include/cub3d.h"

float	rgrad(t_line_necessary *line)
{
	float	dx;
	float	dy;

	dx = line->p2.x - line->p1.x;
	dy = line->p2.y - line->p1.y;
	if (dx == 0)
		return (1);
	else
		return (dy / dx);
}

int	steepness(t_line_necessary *line)
{
	t_point	swap;
	int		steep;

	steep = 1000;
	if (abs(line->p2.y - line->p1.y) > abs(line->p2.x - line->p1.x))
	{
		swap = line->p1;
		line->p1.x = swap.y;
		line->p1.y = swap.x;
		swap = line->p2;
		line->p2.x = swap.y;
		line->p2.y = swap.x;
		steep = 1;
	}
	if (line->p1.x > line->p2.x)
	{
		swap = line->p2;
		line->p2 = line->p1;
		line->p1 = swap;
		line->p1.color = line->p2.color;
		if (steep != 1)
			steep = 0;
	}
	return (steep);
}

float	partone(t_line_necessary *line, float grad, mlx_image_t *image,
		int steep)
{
	int	xend;
	int	yend;
	int	xhole;
	int	truc;

	xend = line->p1.x;
	yend = line->p1.y + grad * (xend - line->p1.x);
	xhole = floatipart(line->p1.x + 0.5);
	truc = floor(yend);
	if (steep == 1)
		first_point_steep(line, xend, image, truc);
	else
	{
		my_mlx_pixel_put(image, xend, truc, color(line->p1.color, 1));
		my_mlx_pixel_put(image, xend, truc + 1, color(line->p1.color, 0.5));
	}
	(void)image;
	return (yend + grad);
}

void	parttwo(t_line_necessary *line, float grad, mlx_image_t *image,
																int steep)
{
	int	xend;
	int	yend;
	int	xhole;
	int	truc;

	xend = line->p2.x;
	yend = line->p2.y + grad * (xend - line->p2.x);
	xhole = floatipart(line->p2.x + 0.5);
	truc = floor(yend);
	if (steep == 1)
		last_point_steep(line, xend, image, truc);
	else
	{
		my_mlx_pixel_put(image, xend, truc, color(line->p2.color, 1));
		my_mlx_pixel_put(image, xend, truc + 1, color(line->p2.color, 0.5));
	}
}

void	line(t_line_necessary *line, mlx_image_t *image)
{
	float	grad;
	int		steep;
	float	place;

	steep = steepness(line);
	grad = rgrad(line);
	place = partone(line, grad, image, steep);
	parttwo(line, grad, image, steep);
	if (steep == 1)
		not_steep_line(line, place, image, grad);
	else
		steepness_draw_line(line, place, image, grad);
}

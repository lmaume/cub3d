#include "../include/cub3d.h"

int	integerpart(float x)
{
	return (floor(x));
}

int	roundbottom(float x)
{
	return (floor(x + 0.5));
}

float	floatpart(float x)
{
	return (x - integerpart(x));
}

float	floatipart(float x)
{
	return (1 - floatpart(x));
}

int	unit_circle(double angle, bool x_or_y)
{
	if (x_or_y)
	{
		if (angle > 0 && angle < PI)
			return (1);
	}
	else if (!x_or_y)
	{
		if (angle > (PI / 2) && angle < (3 * PI) / 2)
			return (1);
	}
	return (0);
}

#include "../include/cub3d.h"

uint32_t	transform(char *str)
{
	uint32_t	result;
	int			i;

	result = 0;
	i = 0;
	if (str == NULL)
		return (-1);
	if (ft_strlen(str) > 8)
		return (0xFFFFFF00);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			result = result * 16 + (str[i] - '0');
		else if (ft_isalpha(str[i]) == 1)
		{
			if (str[i] == 'A' || str[i] == 'B' || str[i] == 'C'\
			|| str[i] == 'D' || str[i] == 'E' || str[i] == 'F')
				result = result * 16 + (str[i] - 55);
		}
		i++;
	}
	result = result * 16 * 16;
	return (result);
}

uint32_t	itox(float opacity)
{
	uint32_t	result;

	result = 0x00000000;
	opacity = floor(opacity * 255);
	result += opacity;
	return (result);
}

uint32_t	color(char *colorpoint, float opacity)
{
	uint32_t	result;
	uint32_t	opa;

	opa = itox(opacity);
	result = transform(colorpoint);
	result += opa;
	return (result);
}

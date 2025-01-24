#include "parsing.h"

int	parse_struct(t_map *data)
{
	t_map	data_map;

	if (init_struct(&data_map) == 1)
		return (1);
	return (0);
}

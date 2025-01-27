#include "parsing/parsing.h"

int	main(int argc, char **argv)
{
	t_map	data_map;

	ft_bzero(&data_map, sizeof(t_map));
	if (is_entry_valid(argc, argv) != 0)
		return (1);
	parse_struct(&data_map, argv[1]);
	//free_map(&data_map);
	return (0);
}

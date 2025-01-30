#include "parsing/parsing.h"

int	main(int argc, char **argv)
{
	t_map	data_map;

	ft_bzero(&data_map, sizeof(t_map));
	if (is_entry_valid(argc, argv) != 0)
		return (1);
	parse_struct(&data_map, argv[1]);
	close_textures(data_map.data);
	free_tab(data_map.map_cpy);
	free_tab(data_map.data.map);
	return (0);
}

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_data_map
{
	char	**map;
	int		north_fd;
	int		south_fd;
	int		east_fd;
	int		west_fd;
	char	*floor;
	char	*ceiling;
}			t_data_map;

typedef struct s_data_paths
{
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	t_data_map	data;
}				t_map;

//? PRINTS
void	print_struct(t_map *data_map);

//? ENTRY
int		is_entry_valid(int argc, char **argv);

//? STRUCT
int		parse_struct(t_map *data, char *filename);
int		init_struct(t_map *data_map, char *filename);

//? FREE
void	free_map(t_map *data_map);

#endif
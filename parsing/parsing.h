#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_map_data
{
	char **map;
	char *north;
	char *south;
	char *east;
	char *west;
	char *floor;
	char *ceiling;
}			t_map;

#endif
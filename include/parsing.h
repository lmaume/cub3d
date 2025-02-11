#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_textures
{
	mlx_image_t	*north_image;
	mlx_image_t	*south_image;
	mlx_image_t	*east_image;
	mlx_image_t	*west_image;
}				t_textures;


typedef struct s_data_map
{
	char		**map;
	int			p_x;
	int			p_y;
	char		p_side;
	int			height;
	int			width;
	char		*floor;
	char		*ceiling;
	t_textures	textures;
}				t_data_map;

typedef struct s_data_paths
{
	char		**map_cpy;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	int			last_x;
	int			last_y;
	t_data_map	data;
	t_eve		*eve;
}				t_map;

//?		PRINTS

//?		ENTRY
int		is_entry_valid(int argc, char **argv);

//?		STRUCT
int		init_struct(t_map *data_map, char *filename);
int		parse_struct(t_map *data, char *filename);
int		player_count(t_map *data_map);

//?		MEMORY
int		map_alloc(t_map *data_map, char **tab);
void	close_images(t_map data_map);

#endif
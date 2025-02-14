#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include "MLX42/MLX42.h"
# include "../libft/libft.h"

typedef struct s_eve t_eve;

typedef struct s_textures
{
	mlx_image_t		*north_image;
	mlx_image_t		*south_image;
	mlx_image_t		*east_image;
	mlx_image_t		*west_image;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*west_texture;
}				t_textures;

typedef struct s_data_map
{
	char		**map;
	char		**file_content;
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
}				t_map;

//?		PRINTS

//?		ENTRY
int		is_entry_valid(int argc, char **argv);

//?		STRUCT
int		open_texture(t_eve *eve);
int		init_struct(t_map *data_map, char *filename);
int		parse_struct(t_map *data, char *filename);
int		player_count(t_map *data_map);

//?		MEMORY
int		map_alloc(t_map *data_map, char **tab);

#endif
NAME	:= cub3d
CC		:= cc
CFLAGS	:= -g3 -O3 -ffast-math -Werror -Wall -Wextra
LIBMLX	:= ./MLX42
HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBFT	:= ./libft/libft.a

MLX_DIR	:= ./MLX42
MLX_A	:= $(MLX_DIR)/build/libmlx42.a

SRCS	:= 	srcs/main.c					\
			parsing/init_map.c			\
			parsing/get_map.c			\
			parsing/parsing.c			\
			srcs/maths_utils.c			\
			srcs/init_struct.c			\
			srcs/character.c			\
			srcs/collide.c				\
			srcs/create_a_line.c		\
			srcs/create_line_part_2.c	\
			srcs/line_utils.c			\
			srcs/matrix_rotation.c		\
			srcs/moves.c				\
			srcs/wall.c					\
			srcs/walls_utils.c			\
			srcs/colors.c				\
			srcs/third_dimention.c		\
			srcs/draw_textures.c		\
			srcs/draw_textures_2.c		\
			srcs/raycasting.c			\
			srcs/ini_struct_2.c			\
			

OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

$(MLX_DIR):
	@git clone https://github.com/codam-coding-college/MLX42.git

$(MLX_A): $(MLX_DIR)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@echo "MLX SUCESSUFLLY ARCHIVED"

mlx: $(MLX_A)

mdestroy:
	@rm -fr $(LIBMLX)

 %.o: %.c
	 @$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(LIBFT) - C ./libft/*.o ./libft/*.a ./libft/*/*.o
	@rm -rf $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft


re: fclean all

.PHONY: all, clean, fclean, re, libmlx

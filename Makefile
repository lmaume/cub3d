NAME	:= cub3d
CC		:= cc
CFLAGS	:= -Werror -Wextra -Wall -g3 #-fsanitize=leak
LIBMLX	:= ./MLX42
HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBFT	:= ./libft/libft.a
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

OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

.built:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	touch .built

 %.o: %.c
	 @$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) $(LIBFT) .built
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(MAKE FCLEAN) - C ./libft/*.o ./libft/*.a
	@rm -rf $(NAME)
	@rm -f .built

$(LIBFT):
	$(MAKE) -C ./libft


re: fclean all

.PHONY: all, clean, fclean, re, libmlx

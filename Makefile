NAME = so_long

MLX_A = MLX42/libmlx42.a

HEADERS	= -I ./include -I $(LIBMLX)/include

LIBS	= -Iinclude -ldl -lglfw -pthread -lm

SRCS =	main.c \
		parsing/init_map.c \
		parsing/parsing.c 

PRINTF = ./printf/libftprintf.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

RM = rm -f

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) all -C ./printf
	@cp $(PRINTF) $(NAME)
	@cc $(CFLAGS) $(LIBS)  $(OBJS) $(PRINTF) $(MLX_A) -o $(NAME)

clean :
	@$(MAKE) clean -C ./printf
	@$(RM) $(OBJS)

fclean : clean
	@$(MAKE) fclean -C ./printf
	@$(RM) $(NAME)

re : fclean all
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 15:13:38 by lmaume            #+#    #+#              #
#    Updated: 2025/01/27 14:32:29 by lmaume           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# printf a ete enleve et strlen est celui de gnl car plus securise

SRCS =	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_memset.c \
		ft_memmove.c \
		ft_memcpy.c \
		ft_bzero.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_tabchr.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c\
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_print_tab.c \
		ft_file_to_tab.c \
		ft_check_line.c \
		ft_count_selected_char_in_tab.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		type_select/ft_type_c.c \
		type_select/ft_type_d.c \
		type_select/ft_type_i.c \
		type_select/ft_type_p.c \
		type_select/ft_type_d.c \
		type_select/ft_type_porcent.c \
		type_select/ft_type_s.c \
		type_select/ft_type_u.c \
		type_select/ft_type_x.c \
		type_select/ft_type_xmaj.c \
		utils/ft_hexa_converter.c \
		utils/ft_ptr_to_hexa.c \
		utils/ft_positive_itoa.c \
		utils/ft_str_toupper.c \
		get_next_line/get_next_line_utils.c \
		get_next_line/get_next_line.c \

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

RM = rm -f

OBJS = $(SRCS:.c=.o)

all : $(NAME)
	
$(NAME) : $(OBJS)
	ar -rc $(NAME) $(OBJS)

clean : 
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

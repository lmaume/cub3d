/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:10:48 by lmaume            #+#    #+#             */
/*   Updated: 2024/11/05 16:42:07 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

int		ft_type_c(int c, int *error);
int		ft_type_d(int d, int *error);
int		ft_type_i(int i, int *error);
int		ft_type_p(void *p, int *error);
int		ft_type_porcent(char c, int *error);
int		ft_type_s(char *s, int *error);
int		ft_type_u(unsigned int u, int *error);
int		ft_type_x(unsigned int x, int *error);
int		ft_type_xmaj(unsigned int x, int *error);
char	*ft_hexa_converter(unsigned int *base_number);
char	*ft_ptr_to_hexa(unsigned long long base_number);
char	*ft_positive_itoa(long long int n);
char	*ft_str_toupper(char *str);
int		ft_printf(const char *str, ...)
		__attribute__ ((format (printf, 1, 2)));

enum e_errors
{
	ERROR_PRINTF = -1,
	CRASH_NULL = -2,
	CRASH_WRITE = -3,
	CRASH_FLAG = -4,
	CRASH_MALLOC = -5
};

#endif

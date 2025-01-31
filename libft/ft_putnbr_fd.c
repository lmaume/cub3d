/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:02:16 by lmaume            #+#    #+#             */
/*   Updated: 2024/01/17 19:46:34 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	char	s;

	if (n < 0)
	{
		if (write(fd, "-", 1) < 0)
			return (-1);
		if (n == -2147483648)
		{
			if (write(fd, "2147483648", 10) < 0)
				return (-1);
			return (1);
		}
		n = n * -1;
	}
	if (n >= 10)
		if (ft_putnbr_fd(n / 10, fd) < 0)
			return (-1);
	s = ((n % 10) + '0');
	return (write(fd, &s, 1));
}

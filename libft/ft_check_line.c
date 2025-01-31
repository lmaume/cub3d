/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:13:49 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/05 17:13:01 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_line_full_of_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i] != c)
			return (false);
		i++;
	}
	return (true);
}

bool	is_started_and_finished_by_c(char *str, char c)
{
	int	len;

	len = ft_strlen(str);
	if (str[0] != c)
		return (false);
	if (str[len - 2] != c)
		return (false);
	return (true);
}

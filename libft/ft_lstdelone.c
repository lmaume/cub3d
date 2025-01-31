/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:32:56 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/13 15:33:25 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **lst, t_list *to_del)
{
	t_list	*bloc;

	bloc = *lst;
	while (bloc->next != to_del)
		bloc = bloc->next;
	free(to_del);
}

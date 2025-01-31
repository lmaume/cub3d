/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:31:56 by lmaume            #+#    #+#             */
/*   Updated: 2024/06/13 15:32:35 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*bloc;

	bloc = ft_calloc(sizeof(t_list), 1);
	bloc->content = content;
	return (bloc);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*bloc;

	bloc = *lst;
	while (bloc->next != NULL)
	{
		bloc = bloc->next;
	}
	bloc->next = new;
	new->next = NULL;
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

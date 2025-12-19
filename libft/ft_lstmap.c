/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:23:13 by mchihime          #+#    #+#             */
/*   Updated: 2025/11/02 12:48:38 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear_map(t_list *lst, void (*del)(void *))
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		del(lst->content);
		free(lst);
		lst = tmp;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	t_list	*tail;

	new_list = NULL;
	tail = NULL;
	while (lst)
	{
		new_node = malloc(sizeof(t_list));
		if (!new_node)
		{
			ft_lstclear_map(new_list, del);
			return (NULL);
		}
		new_node->content = f(lst->content);
		new_node->next = NULL;
		if (!new_list)
			new_list = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		lst = lst->next;
	}
	return (new_list);
}

/*#include <stdio.h>
#include <stdlib.h>

void	*add_one(void *n)
{
	int	*res;

	res = malloc(sizeof(int));
	*res = (*(int *)n) + 1;
	return (res);
}

void	del(void *n)
{
	free(n);
}

int	main(void)
{
	t_list	*list;
	t_list	*new_list;
	int		a = 1;
	int		b = 2;
	int		c = 3;

	list = ft_lstnew(&a);
	ft_lstadd_back(&list, ft_lstnew(&b));
	ft_lstadd_back(&list, ft_lstnew(&c));
	new_list = ft_lstmap(list, add_one, del);
	while (new_list)
	{
		printf("%d\n", *(int *)new_list->content);
		new_list = new_list->next;
	}
	return (0);
}
*/
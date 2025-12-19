/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:06:59 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/23 12:18:30 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_node;
	t_list	*cur;

	if (!lst || !del)
		return ;
	cur = *lst;
	while (cur)
	{
		next_node = cur->next;
		del(cur->content);
		free(cur);
		cur = next_node;
	}
	*lst = NULL;
}

/*void	del(void *content)
{
	free(content);
}
#include <stdio.h>
int	main(void)
{
	t_list	*lst;
	int		*a = malloc(sizeof(int));
	int		*b = malloc(sizeof(int));

	*a = 42;
	*b = 21;
	lst = ft_lstnew(a);
	ft_lstadd_back(&lst, ft_lstnew(b));
	ft_lstclear(&lst, del);
	if (lst == NULL)
		printf("List cleared\n");
	return (0);
}*/

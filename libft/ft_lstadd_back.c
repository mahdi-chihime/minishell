/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:39:54 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/22 17:58:06 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp -> next)
		temp = temp ->next;
	temp ->next = new;
}
/*#include <stdio.h>
int main(void)
{
    int a = 1, b = 2, c = 3;
    t_list *list = NULL;

    ft_lstadd_back(&list, ft_lstnew(&a));
    ft_lstadd_back(&list, ft_lstnew(&b));
    ft_lstadd_back(&list, ft_lstnew(&c));

    while (list)
    {
        printf("%d ", *(int *)list->content);
        list = list->next;
    }

    return 0;
}*/

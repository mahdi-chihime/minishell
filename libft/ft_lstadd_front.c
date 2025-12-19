/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:06:01 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/22 17:10:49 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new -> next = *lst;
	*lst = new;
}
/*#include <stdio.h>
int main(void)
{
    int a = 1, b = 2, c = 3;
    t_list *list = ft_lstnew(&a);
    ft_lstadd_front(&list, ft_lstnew(&b));
    ft_lstadd_front(&list, ft_lstnew(&c));

    t_list *tmp = list;
    while (tmp)
    {
        printf("%d ", *(int *)tmp->content);
        tmp = tmp->next;
    }

    return 0;
}*/

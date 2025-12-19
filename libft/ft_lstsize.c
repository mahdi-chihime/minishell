/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:11:14 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/22 17:17:11 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		x;

	x = 0;
	temp = lst;
	while (temp)
	{
		x++;
		temp = temp -> next;
	}
	return (x);
}
/*#include<stdio.h>
int main(void)
{
    int a = 1, b = 2, c = 3;
    t_list *list = ft_lstnew(&a);
    list->next = ft_lstnew(&b);
    list->next->next = ft_lstnew(&c);

    printf("List size: %d\n", ft_lstsize(list));

    return 0;
}*/

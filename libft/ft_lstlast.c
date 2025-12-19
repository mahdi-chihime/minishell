/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:19:06 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/22 17:38:31 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}
/*#include <stdio.h>
int main(){
	t_list *x;
	int a = 1, b = 2, c = 3;
	x = ft_lstnew(&a);
	x -> next = ft_lstnew(&b);
	x -> next = ft_lstnew(&c);
	t_list *last = ft_lstlast(x);
	printf("%d", *(int *)last -> content);
	return 0;
}*/

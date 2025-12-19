/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihime <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:57:23 by mchihime          #+#    #+#             */
/*   Updated: 2025/05/21 21:23:03 by mchihime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		f(i, &s[i]);
		i++;
	}
}
/*#include <stdio.h>
void	upper(unsigned int i, char *c)
{
	(void)i;
    	if (*c >= 'a' && *c <= 'z')
        	*c = *c - 32;
}
int main(){
	char x[] = "hello";
	ft_striteri(x,upper);
	printf("%s", x);
}*/

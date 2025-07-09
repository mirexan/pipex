/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:21:03 by mregada-          #+#    #+#             */
/*   Updated: 2024/10/11 21:01:13 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	join(char **ptr, char const *str)
{
	while (*str != '\0')
	{
		**ptr = *str;
		(*ptr)++;
		str++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*resultado;
	char	*ptr;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	resultado = (char *)malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (resultado == NULL)
		return (NULL);
	ptr = resultado;
	join(&ptr, s1);
	join(&ptr, s2);
	*ptr = '\0';
	return (resultado);
}

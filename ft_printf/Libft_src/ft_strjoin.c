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

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*resultado;
	char	*ptr;
	size_t	len;

	len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	resultado = (char *)malloc(sizeof(char) * len);
	if (resultado == NULL)
		return (NULL);
	len = 0;
	ptr = resultado;
	while (*s1 != '\0')
	{
		*ptr = *s1;
		ptr++;
		s1++;
	}
	while (*s2 != '\0')
	{
		*ptr = *s2;
		ptr++;
		s2++;
	}
	*ptr = '\0';
	return (resultado);
}

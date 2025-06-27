/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregada- <mregada-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:02:47 by mregada-          #+#    #+#             */
/*   Updated: 2025/06/27 19:02:49 by mregada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t contador)
{
	size_t	i;

	i = 0;
	while (i < contador)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (!s1[i] || !s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

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

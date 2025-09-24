/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <mbouhia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:04:30 by mbouhia           #+#    #+#             */
/*   Updated: 2024/10/25 16:13:38 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_strcat(char *dest, const char *src)
{
	size_t	destlen;
	char	*original;

	original = dest;
	destlen = ft_strlen(dest);
	while (*src)
	{
		*(dest + destlen) = *src;
		destlen++;
		src++;
	}
	*(dest + destlen) = '\0';
	return (original);
}

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joinstrs;
	size_t	size;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	size = ft_strlen(s1) + ft_strlen(s2);
	joinstrs = malloc((size + 1) * (sizeof(char)));
	if (!joinstrs)
		return (NULL);
	ft_strcpy(joinstrs, s1);
	ft_strcat(joinstrs, s2);
	return (joinstrs);
}

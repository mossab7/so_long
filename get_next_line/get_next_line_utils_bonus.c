/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 22:40:21 by mbouhia           #+#    #+#             */
/*   Updated: 2024/11/09 22:40:22 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strcat(char *dest, const char *src)
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

char	*free_stored(char **content)
{
	free(*content);
	*content = NULL;
	return (NULL);
}

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(src);
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	len = 0;
	while (src[len])
	{
		dest[len] = src[len];
		len++;
	}
	dest[len] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joinstrs;
	size_t	size;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	size = ft_strlen(s1) + ft_strlen(s2);
	joinstrs = malloc((size + 1) * sizeof(char));
	if (!joinstrs)
		return (NULL);
	size = 0;
	while (s1[size])
	{
		joinstrs[size] = s1[size];
		size++;
	}
	joinstrs[size] = '\0';
	ft_strcat(joinstrs, s2);
	return (joinstrs);
}

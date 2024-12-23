/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <mbouhia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:04:33 by mbouhia           #+#    #+#             */
/*   Updated: 2024/10/25 21:03:43 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static int	ft_issep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	size;
	size_t	start;
	size_t	end;
	char	*trimstr;

	if (!s)
		return (NULL);
	start = 0;
	while (ft_issep(s[start], (char *)set))
		start++;
	end = start;
	while (s[end])
		end++;
	while (ft_issep(s[end - 1], (char *)set) && end > start)
		end--;
	size = end - start;
	trimstr = (char *)malloc((size + 1) * sizeof(char));
	if (!trimstr)
		return (NULL);
	ft_strncpy(trimstr, (s + start), size);
	trimstr[size] = '\0';
	return (trimstr);
}

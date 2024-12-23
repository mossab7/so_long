/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <mbouhia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:04:28 by mbouhia           #+#    #+#             */
/*   Updated: 2024/10/26 12:37:00 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_wordlen(const char *str, char c)
{
	size_t	len;

	len = 0;
	while (*str && *str == c)
		str++;
	while (*str && !(*str == c))
	{
		len++;
		str++;
	}
	return (len);
}

static size_t	ft_countwords(char *str, char c)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == c))
			i++;
		if (str[i] && !(str[i] == c))
			len++;
		while (str[i] && !(str[i] == c))
			i++;
	}
	return (len);
}

static void	*free_str(char ***strptr, size_t j)
{
	if (strptr && *strptr)
	{
		while (j > 0)
			free((*strptr)[--j]);
		free(*strptr);
	}
	return (NULL);
}

char	**ft_split(char *str, char c)
{
	size_t	j;
	size_t	strlen;
	char	**strptr;

	if (!str)
		return (NULL);
	j = ft_countwords(str, c);
	strptr = (char **)malloc((j + 1) * sizeof(char *));
	if (strptr == NULL)
		return (NULL);
	j = 0;
	while (*str)
	{
		while ((*str == c) && *str != '\0')
			str++;
		if (*str == '\0')
			break ;
		strlen = ft_wordlen(str, c);
		strptr[j++] = ft_substr(str, 0, strlen);
		if (!strptr[j - 1])
			return (free_str(&strptr, --j));
		str += strlen;
	}
	strptr[j] = NULL;
	return (strptr);
}

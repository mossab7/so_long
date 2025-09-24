/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <mbouhia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:04:23 by mbouhia           #+#    #+#             */
/*   Updated: 2024/10/23 09:18:31 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_numlen(int n)
{
	long	nb;
	int		sign;
	size_t	len;

	nb = n;
	sign = (n < 0);
	len = 0;
	if (nb == 0)
		return (1);
	if (sign)
		nb = -nb;
	while (nb)
	{
		len++;
		nb /= 10;
	}
	return (len + sign);
}

char	*ft_itoa(int n)
{
	size_t	len;
	long	nb;
	int		sign;
	char	*number;

	len = ft_numlen(n);
	sign = (n < 0);
	number = (char *)allocate_tracked_memory((len + 1) * sizeof(char));
	if (!number)
		return (NULL);
	nb = n;
	if (sign)
	{
		nb = -nb;
		number[0] = '-';
	}
	number[len] = '\0';
	while (len > (size_t)sign)
	{
		number[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (number);
}

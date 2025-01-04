/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_manager_utiles.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:52:29 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/04 15:52:31 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	cleanup_memory_tracker(t_alloc_record **memory_records)
{
	t_alloc_record	*current;
	t_alloc_record	*next;

	if (!memory_records || !*memory_records)
		return ;
	current = *memory_records;
	while (current != NULL)
	{
		next = current->next;
		if (current->free_func && current->ptr)
		{
			current->free_func(current->ptr);
		}
		free(current);
		current = next;
	}
	*memory_records = NULL;
}

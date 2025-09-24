/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 15:52:16 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/04 15:52:18 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

t_alloc_record	**get_memory_tracker(void)
{
	static t_alloc_record	*memory_records;

	return (&memory_records);
}

t_alloc_record	*create_memory_record(void *ptr, void (*deallocator)(void *))
{
	t_alloc_record	*new_record;

	new_record = malloc(sizeof(t_alloc_record));
	if (!new_record)
		return (NULL);
	new_record->ptr = ptr;
	new_record->free_func = deallocator;
	new_record->next = NULL;
	return (new_record);
}

void	register_memory_allocation(t_alloc_record **memory_records,
		t_alloc_record *new_record)
{
	t_alloc_record	*current;

	if (!new_record)
		return ;
	if (!*memory_records)
	{
		*memory_records = new_record;
		return ;
	}
	current = *memory_records;
	while (current->next)
		current = current->next;
	current->next = new_record;
}

void	handle_allocation_failure(void *ptr)
{
	if (ptr == NULL)
	{
		cleanup_memory_tracker(get_memory_tracker());
		fprintf(stderr, "Fatal: Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
}

void	*allocate_tracked_memory(size_t size)
{
	void	*ptr;

	ptr = ft_calloc(size, 1);
	handle_allocation_failure(ptr);
	register_memory_allocation(get_memory_tracker(), create_memory_record(ptr,
			free));
	return (ptr);
}

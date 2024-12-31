#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

t_alloc_record **get_instance(void)
{
    static t_alloc_record *alloc_record;
    return (&alloc_record);
}

t_alloc_record *create_new_node(void *ptr, void (*f)(void *), size_t size)
{
    t_alloc_record *new_node;

    new_node = malloc(sizeof(t_alloc_record));
    if (!new_node)
        return (NULL);
    new_node->ptr = ptr;
    new_node->free_func = f;
    new_node->size = size;
    new_node->next = NULL;
    return (new_node);
}

void add_allocation_to_list(t_alloc_record **alloc_record, t_alloc_record *new_node)
{
    t_alloc_record *current;

    if (!new_node)
        return;
    if (!*alloc_record)
    {
        *alloc_record = new_node;
        return;
    }
    current = *alloc_record;
    while (current->next)
        current = current->next;
    current->next = new_node;
}

void check_alloc(void *ptr)
{
    if (ptr == NULL)
    {
        free_alloc(get_instance());
        printf("Allocation failed\n");
        exit(1);
    }
}

void *track_alloc(size_t size)
{
    void *ptr;

    ptr = ft_calloc(size,1);
    check_alloc(ptr);
    add_allocation_to_list(get_instance(), create_new_node(ptr, free, size));
    return (ptr);
}

void free_alloc(t_alloc_record **alloc_record)
{
    t_alloc_record *current;
    t_alloc_record *next;

    current = *alloc_record;
    while (current != NULL)
    {
        next = current->next;
        if (current->free_func && current->ptr)
            current->free_func(current->ptr);
        free(current);
        current = next;
    }
    *alloc_record = NULL;
}


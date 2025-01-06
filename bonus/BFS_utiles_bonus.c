/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BFS_utiles_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouhia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:47:12 by mbouhia           #+#    #+#             */
/*   Updated: 2025/01/05 21:18:30 by mbouhia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_stack(t_stack *stack)
{
	if (!stack)
		return ;
	if (stack->points)
		free(stack->points);
	free(stack);
}

t_stack	*create_stack(int capacity)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	stack->points = malloc(sizeof(t_point) * capacity);
	stack->top = -1;
	stack->capacity = capacity;
	return (stack);
}

void	push(t_stack *stack, t_point point)
{
	if (stack->top < stack->capacity - 1)
		stack->points[++stack->top] = point;
}

t_point	pop(t_stack *stack)
{
	return (stack->points[stack->top--]);
}

int	is_empty(t_stack *stack)
{
	return (stack->top == -1);
}

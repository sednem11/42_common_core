#include "ft_push_swap.h"

void	assign_cost(t_stack *stack_a, t_stack **stack_b)
{
	t_stack *current;

	current = *stack_b;
	while (current != NULL)
	{
		current->cost = bestfriend_moves(stack_a, *stack_b, current);
		current = current->next;
	}
}

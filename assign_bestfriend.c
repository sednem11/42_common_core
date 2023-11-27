#include "ft_push_swap.h"

void	assign_bestfriend(t_stack **stack_a, t_stack *stack_b)
{
	while (stack_b != NULL)
	{
		stack_b->bestfriend = find_bestfriend(stack_a, stack_b);
		stack_b = stack_b->next;
	}
}

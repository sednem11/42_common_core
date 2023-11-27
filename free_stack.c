#include "ft_push_swap.h"

void	free_stack(t_stack **stack_a)
{
	t_stack		*current;

	while ((*stack_a) != NULL)
	{
		current = (*stack_a)->next;
		free ((*stack_a));
		(*stack_a) = current;
	}
}

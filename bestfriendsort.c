#include "ft_push_swap.h"

t_stack	*find_bestfriend(t_stack **stack_a, t_stack *stack_b1)
{
	t_stack	*current;
	t_stack *current2;

	current = (*stack_a);
	while (current != NULL)
	{
		if (current->content > stack_b1->content)
		{
			current2 = current;
			while (current2 != NULL)
			{
				if (current->content > current2->content && current2->content > stack_b1->content)
					current = current2;
				current2 = current2->next;
			}
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

/*

stack_a :  stack_b:
 7				6
 8				4
 9				5


*/
#include "ft_push_swap.h"

void	move_down_a(t_stack **stack_a, t_stack *b1)
{
	while ((*stack_a) != find_bestfriend(stack_a, b1))
	{
		revrotatea(stack_a);
	}
}

void	move_down(t_stack **stack_b, t_stack *b1)
{
	while ((*stack_b) != b1)
	{
		revrotateb(stack_b);
	}
}

void	move_up(t_stack **stack_b, t_stack *b1)
{
	while ((*stack_b) != b1)
	{
		rotateb(stack_b);
	}
}

void	move_stack_a(t_stack **stack_a, t_stack **stack_b)
{
	int		i;
	int		n;
	t_stack	*current;
	
	current = (*stack_a);
	n = 0;
	i = 0;
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	current = (*stack_a);
	while (current != find_bestfriend(stack_a, (*stack_b)))
	{
		current = current->next;
		n++;
	}
	if (n <= i / 2)
	{
		while ((*stack_a) != find_bestfriend(stack_a, (*stack_b)))
			rotatea(stack_a);
	}
	else
		move_down_a(stack_a, (*stack_b));
}

void	move_less_cost(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*current;
	int		i;
	int		n;

	n = 0;
	i = 0;
	current = (*stack_b);
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	current = (*stack_b);
	while (current != less_cost((*stack_b)))
	{
		current = current->next;
		n++;
	}
	if (n <= i / 2)
		move_up(stack_b, less_cost((*stack_b)));
	else
		move_down(stack_b, less_cost((*stack_b)));
	move_stack_a(stack_a, stack_b);
	pusha(stack_b, stack_a);
}

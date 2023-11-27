#include "ft_push_swap.h"

int		thisthing(t_stack *current)
{
	int		len;

	len = 0;
	while (current != NULL)
	{
		current = current->next;
		len++;
	}
	return (len);
}

int		thatthing(t_stack *current)
{
	int		sum;

	sum = 0;
	while (current != NULL)
	{
		sum += (current->content);
		current = current->next;
	}
	return (sum);
}

void	sort3(t_stack **stack_a)
{
	if ((*stack_a)->content > ((*stack_a)->next)->content)
		swapa(stack_a);
	if (((*stack_a)->next)->content > (((*stack_a)->next)->next)->content)
	{
		if((((*stack_a)->next)->next)->content > (*stack_a)->content)
		{
			revrotatea(stack_a);
			swapa(stack_a);
		}
		else
			revrotatea(stack_a);
	}
}

void	first_push_b(t_stack **stack_a, t_stack **stack_b)
{
	int		len;
	int		sum;
	int		average;

	len = thisthing(*stack_a);
	while (len > 3)
	{
		sum = thatthing(*stack_a);
		average = (sum / len);
		if ((*stack_a)->content < average)
			pushb(stack_a, stack_b);
		else
			rotatea(stack_a);
		len = thisthing(*stack_a);
	}
}

void	sort(t_stack **stack_a, t_stack **stack_b)
{
	int		len;

	len = thisthing(*stack_a);
	if (len == 3)
		sort3(stack_a);
	if (len == 2)
	{
		if ((*stack_a)->content > ((*stack_a)->next)->content)
			swapa(stack_a);
	}
	else
	{
		first_push_b(stack_a, stack_b);
		sort3(stack_a);	
		{
			while ((*stack_b) != NULL)
			{
				assign_bestfriend(stack_b, (*stack_b));
				assign_bestfriend(stack_a, (*stack_b));
				assign_cost((*stack_a), stack_b);
				move_less_cost(stack_a, stack_b);
			}
		}
	}
	last_sort((*stack_a));
}

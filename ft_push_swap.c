/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:57:53 by macampos          #+#    #+#             */
/*   Updated: 2023/11/27 15:24:25 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int		check_if_sorted(t_stack **stack_a)
{
	t_stack	*current;

	current = (*stack_a);
	while (current->next != NULL)
	{
		if (current->content > (current->next)->content)
			return (1);
		current = current->next;
	}
	return (0);
}

int		check_if_no_doubles(t_stack **stack_a)
{
	t_stack *current;
	t_stack *current2;

	current2 = (*stack_a);
	current = (*stack_a);
	while (current->next != NULL)
	{
		while (current2->next != NULL)
		{
			current2 = current2->next;
			if (current->content == current2->content)
				return (1);
		}
		current = current->next;
		current2 = current;
	}
	return (0);
}

t_stack	*make_stack(char *argv[], t_stack *stack_a, t_stack *first_a, t_stack *current)
{
	int	x;
	int i;
	char **str;

	i = 1;
	while (argv[i])
	{
		str = ft_split(argv[i], ' ');
		x = 0;
		while (str[x])
		{
			first_a = create_node(ft_atoi(str[x]));
			if (!stack_a)
				stack_a = first_a;
			else
				current->next = first_a;
			free(str[x]);
			current = first_a;
			x++;
		}		
		free(str);
		i++;
	}
	
	return stack_a;
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	t_stack	*first_a;
	t_stack *current;

	stack_a = NULL;
	first_a = NULL;
	current = NULL;
	stack_b = NULL;
	if (argc < 2)
		return (0);
	stack_a = make_stack(argv, stack_a, first_a, current);
	if (check_if_no_doubles(&stack_a) == 1)
		ft_printf("%s\n", "Error");
	else
	{
		if (check_if_sorted(&stack_a) == 1)
			sort(&stack_a, &stack_b);
		free_stack(&stack_a);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:57:53 by macampos          #+#    #+#             */
/*   Updated: 2023/12/07 16:26:33 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

int	check_if_sorted(t_stack **stack_a)
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

t_stack	*check_create_node(char *str)
{
	char	*temp;
	int		temp1;

	temp1 = ft_atoi(str);
	temp = ft_itoa(temp1);
	if (!temp1 && str[0] != '0')
	{
		free(temp);
		ft_printf("%s\n", "Error");
		return (NULL);
	}
	if (!ft_strncmp(str, temp, ft_strlen(str)))
	{
		free(temp);
		free(str);
		return (create_node(temp1));
	}
	else
	{
		free(temp);
		ft_printf("%s\n", "Error");
		return (NULL);
	}
}

typedef struct s_stupid
{
	int		x;
	int		i;
	char	**str;
}			t_stupid;

t_stack	*make_stack(char *argv[], t_stack *stack_a, t_stack *first_a,
		t_stack *current)
{
	struct s_stupid	stupid;

	stupid.i = 1;
	while (argv[stupid.i])
	{
		stupid.str = ft_split(argv[stupid.i], ' ');
		stupid.x = 0;
		while (stupid.str[stupid.x])
		{
			first_a = check_create_node(stupid.str[stupid.x]);
			if (second_free(first_a, stupid.str, stupid.x) == 0)
				break ;
			if (!stack_a)
				stack_a = first_a;
			else
				current->next = first_a;
			current = first_a;
			stupid.x++;
		}
		if (first_free(first_a, stupid.str, &stack_a) == 0)
			break ;
		free(stupid.str);
		stupid.i++;
	}
	return (stack_a);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	t_stack	*first_a;
	t_stack	*current;

	stack_a = NULL;
	first_a = NULL;
	current = NULL;
	stack_b = NULL;
	if (argc < 2)
		return (0);
	stack_a = make_stack(argv, stack_a, first_a, current);
	if (!stack_a)
		return (0);
	if (check_if_no_doubles(&stack_a) == 1)
		ft_printf("%s\n", "Error");
	else
	{
		if (check_if_sorted(&stack_a) == 1)
			sort(&stack_a, &stack_b);
		free_stack(&stack_a);
	}
}

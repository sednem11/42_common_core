/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:03:16 by macampos          #+#    #+#             */
/*   Updated: 2023/12/26 19:37:05 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

void	checker_runner(t_stack **stack_a, t_stack **stack_b, char *l)
{
	if (l[0] == 's' && l[1] == 'a' && l[2] == '\n')
		bonusswapa(stack_a);
	else if (l[0] == 's' && l[1] == 'b' && l[2] == '\n')
		bonusswapb(stack_b);
	else if (l[0] == 'r' && l[1] == 'r' && l[2] == 'a' && l[3] == '\n')
		bonusrevrotatea(stack_a);
	else if (l[0] == 'r' && l[1] == 'r' && l[2] == 'b' && l[3] == '\n')
		bonusrevrotateb(stack_b);
	else if (l[0] == 'r' && l[1] == 'a' && l[2] == '\n')
		bonusrotatea(stack_a);
	else if (l[0] == 'r' && l[1] == 'b' && l[2] == '\n')
		bonusrotateb(stack_b);
	else if (l[0] == 'p' && l[1] == 'a' && l[2] == '\n')
		bonuspusha(stack_b, stack_a);
	else if (l[0] == 'p' && l[1] == 'b' && l[2] == '\n')
		bonuspushb(stack_a, stack_b);
}

typedef struct s_stupid
{
	int		x;
	int		i;
	char	**str;
	int		z;
	t_stack	*current;
	t_stack	*stack_a;
	t_stack	*first_a;
	t_stack	*stack_b;
	char	*line;
}			t_stupid;

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
	struct s_stupid	stupid;

	stupid.stack_a = NULL;
	stupid.first_a = NULL;
	stupid.current = NULL;
	stupid.stack_b = NULL;
	if (argc < 2)
		return (0);
	stupid.stack_a = make_stack(argv, stupid.stack_a,
			stupid.first_a, stupid.current);
	if (!stupid.stack_a)
		return (0);
	if (check_if_no_doubles(&stupid.stack_a) == 0)
	{
		stupid.line = get_next_line(0);
		while (stupid.line != NULL)
		{
			checker_runner(&stupid.stack_a, &stupid.stack_b, stupid.line);
			free(stupid.line);
			stupid.line = get_next_line(0);
		}
		errorok(stupid.stack_a);
	}
	else
		ft_printf("%s\n", "Error");
}

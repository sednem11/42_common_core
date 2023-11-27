/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:57:22 by macampos          #+#    #+#             */
/*   Updated: 2023/11/21 20:06:13 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct	s_stack
{
	int				content;
	int				cost;
	struct s_stack	*next;
    struct s_stack  *bestfriend;
}					t_stack;

t_stack	*create_node(int content);
void	pusha(t_stack **stack_a, t_stack **stack_b);
void	swapa(t_stack **stack_a);
void	rotatea(t_stack **stack_a);
void	revrotatea(t_stack **stack_a);
void	pushb(t_stack **stack_b, t_stack **stack_a);
void	swapb(t_stack **stack_b);
void	rotateb(t_stack **stack_b);
void	revrotateb(t_stack **stack_b);
void	sort(t_stack **stack_a, t_stack **stack_b);
t_stack	*find_bestfriend(t_stack **stack_a, t_stack *stack_b1);
void	assign_bestfriend(t_stack **stack_a, t_stack *stack_b);
int		bestfriend_moves(t_stack *stack_a, t_stack *stack_b, t_stack *b1);
void	assign_cost(t_stack *stack_a, t_stack **stack_b);
t_stack	*less_cost(t_stack *stack_b);
void	move_less_cost(t_stack **stack_a, t_stack **stack_b);
void	free_stack(t_stack **stack_a);
void	last_sort(t_stack *stack_a);

#endif
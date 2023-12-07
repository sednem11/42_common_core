/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:57:22 by macampos          #+#    #+#             */
/*   Updated: 2023/12/07 16:27:38 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PUSH_SWAP_H
# define FT_PUSH_SWAP_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct s_stack
{
	int				content;
	int				cost;
	struct s_stack	*next;
	struct s_stack	*bestfriend;
}					t_stack;

t_stack				*create_node(int content);
void				pusha(t_stack **stack_a, t_stack **stack_b);
void				swapa(t_stack **stack_a);
void				rotatea(t_stack **stack_a);
void				revrotatea(t_stack **stack_a);
void				pushb(t_stack **stack_b, t_stack **stack_a);
void				swapb(t_stack **stack_b);
void				rotateb(t_stack **stack_b);
void				revrotateb(t_stack **stack_b);
void				bonuspusha(t_stack **stack_a, t_stack **stack_b);
void				bonusswapa(t_stack **stack_a);
void				bonusrotatea(t_stack **stack_a);
void				bonusrevrotatea(t_stack **stack_a);
void				bonuspushb(t_stack **stack_b, t_stack **stack_a);
void				bonusswapb(t_stack **stack_b);
void				bonusrotateb(t_stack **stack_b);
void				bonusrevrotateb(t_stack **stack_b);
void				sort(t_stack **stack_a, t_stack **stack_b);
t_stack				*find_bestfriend(t_stack **stack_a, t_stack *stack_b1);
void				assign_bestfriend(t_stack **stack_a, t_stack *stack_b);
int					bestfriend_moves(t_stack *stack_a, t_stack *stack_b,
						t_stack *b1);
void				assign_cost(t_stack *stack_a, t_stack **stack_b);
t_stack				*less_cost(t_stack *stack_b);
void				move_less_cost(t_stack **stack_a, t_stack **stack_b);
void				free_stack(t_stack **stack_a);
void				last_sort(t_stack **stack_a);
int					first_free(t_stack *first_a, char **str, t_stack **stack_a);
int					second_free(t_stack *first_a, char **str, int x);
int					main(int argc, char **argv);
int					check_if_no_doubles(t_stack **stack_a);

#endif
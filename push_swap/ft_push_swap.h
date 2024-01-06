/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:57:22 by macampos          #+#    #+#             */
/*   Updated: 2024/01/06 18:23:12 by macampos         ###   ########.fr       */
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
void				pusha(t_stack **stack_b, t_stack **stack_a);
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
void				rotateallbonus(t_stack **stack_a, t_stack **stack_b);
void				revrotateallbonus(t_stack **stack_a, t_stack **stack_b);
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
void				errorok(t_stack *stack_a);
int					check_if_sorted(t_stack **stack_a);
void				rotateall(t_stack **stack_a, t_stack **stack_b);
void				rotateball(t_stack **stack_b);
void				rotateaall(t_stack **stack_a);
void				revrotateall(t_stack **stack_a, t_stack **stack_b);
void				rotateball(t_stack **stack_b);
int					move_all(t_stack **stack_a, t_stack **stack_b, int z,
						t_stack *b1);
void				sort2(t_stack **stack_a);
void				sort3(t_stack **stack_a);
void				first_push_b(t_stack **stack_a, t_stack **stack_b);
void				sort5(t_stack **stack_a, t_stack **stack_b);
int					move_stack_a(t_stack **stack_a, t_stack **stack_b, int z);
int					location(t_stack **stack_a, t_stack *stack_b);
int					thisthing(t_stack *current);

#endif
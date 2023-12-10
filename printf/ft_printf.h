/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:41:38 by macampos          #+#    #+#             */
/*   Updated: 2023/10/12 16:09:34 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define HEX_UPP_BASE "0123456789ABCDEF"
# define HEX_LOW_BASE "0123456789abcdef"

int		ft_printf(const char *str, ...);
void	ft_putchar(char c, long int *counter);
void	ft_putstr(const char *str, long int *counter);
void	ft_putnum(int num, long int *counter);
void	ft_unint(unsigned int num, long int *counter);
void	ft_puthex(unsigned long int num, long int *counter, int p, int caps);
void	ft_check(char *str, va_list args, int i, long int *char_ttl);

#endif
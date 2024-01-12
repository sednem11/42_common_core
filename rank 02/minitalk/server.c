/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:55:11 by macampos          #+#    #+#             */
/*   Updated: 2024/01/09 17:58:53 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"

char	received_message[256];

volatile sig_atomic_t flag = 0;

void	signal_handler(int signal)
{
	if (signal == SIGUSR1)
		flag = 1;
}

int	main(void)
{
	int	PID;

	PID = getpid();
	ft_printf("PID: %i\n", PID);
	signal(SIGUSR1, signal_handler);
	while (!flag)
		sleep(1);
	ft_printf("%s\n", received_message);
}
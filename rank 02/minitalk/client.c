/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:55:06 by macampos          #+#    #+#             */
/*   Updated: 2024/01/09 17:59:56 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"

int	main(int argc, char **argv)
{
	int		i;
	int		n;
	int		PID;
	int		result;
	char	*line;

	i = 0;
	n = 2;
	if (argc < 2)
		return (0);
	PID = ft_atoi(argv[1]);
	result = kill(PID, SIGUSR1);
	if (result == -1) {
		ft_printf("%s\n", "Error with the PID");
		return (-1);
	}
	line = argv[2];
	ft_strlcpy(received_message, line, ft_strlen(line));
}

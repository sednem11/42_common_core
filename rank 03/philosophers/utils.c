/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:42:40 by macampos          #+#    #+#             */
/*   Updated: 2024/03/18 15:00:02 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	print_status(t_philosopher *philo, char *status, int *dead)
{
	pthread_mutex_lock(&philo->table->write);
	if (philo->table->dead)
	{
		pthread_mutex_unlock(&philo->table->write);
		*dead = 1;
		return ;
	}
	printf("%llu %d %s\n", get_time() - philo->table->start_time, philo->id + 1,
		status);
	pthread_mutex_unlock(&philo->table->write);
}

t_time	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	_usleep(t_time time)
{
	t_time	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(10);
}

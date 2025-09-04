/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:33:12 by macampos          #+#    #+#             */
/*   Updated: 2024/04/02 15:35:30 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philosopher *philo, int *dead)
{
	take_forks(philo, dead);
	if (*dead)
		return (0);
	print_status(philo, "is eating", dead);
	philo->last_meal = get_time();
	_usleep(philo->table->time_to_eat);
	unlock_forks(philo->myfork, philo->leftfork);
	philo->mealseaten++;
	if ((philo->table->meals != -1
			&& philo->mealseaten >= philo->table->meals) || *dead)
		return (0);
	return (1);
}

int	is_dead(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->write);
	if (philo->table->dead)
	{
		pthread_mutex_unlock(&philo->table->write);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->write);
	return (0);
}

void	*philo_function(void *arg)
{
	int				dead;
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	dead = 0;
	while (!philo->dead)
	{
		if (is_dead(philo))
			break ;
		if (!eat(philo, &dead))
			break ;
		print_status(philo, "is sleeping", &dead);
		_usleep(philo->table->time_to_sleep);
		if (is_dead(philo))
			break ;
		print_status(philo, "is thinking", &dead);
	}
	return (NULL);
}

void	routine_start(t_table *table)
{
	t_philosopher	*philo;

	philo = table->firstphilo;
	while (philo)
	{
		if (philo->id % 2 == 0)
			pthread_create(&philo->thread, NULL, philo_function, philo);
		philo = philo->next;
		if (philo == table->firstphilo)
			break ;
	}
	philo = table->firstphilo->next;
	while (philo)
	{
		if (philo->id % 2 == 1)
			pthread_create(&philo->thread, NULL, philo_function, philo);
		philo = philo->next;
		if (philo == table->firstphilo)
			break ;
	}
}

void	*join_routines(t_table *table)
{
	t_philosopher	*philo;

	philo = table->firstphilo;
	while (philo)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		if (philo == table->firstphilo)
			break ;
	}
	return (NULL);
}

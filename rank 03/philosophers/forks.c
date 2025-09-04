/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:07:01 by macampos          #+#    #+#             */
/*   Updated: 2024/04/01 19:55:49 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(pthread_mutex_t *myfork, pthread_mutex_t *leftfork)
{
	if (myfork)
		pthread_mutex_unlock(myfork);
	if (leftfork)
		pthread_mutex_unlock(leftfork);
}

void	take_forks(t_philosopher *philo, int *dead)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->leftfork);
		print_status(philo, "has taken a fork", dead);
		if (*dead || philo->table->philosophers == 1)
		{
			*dead = 1;
			return (unlock_forks(NULL, philo->leftfork));
		}
		pthread_mutex_lock(philo->myfork);
		print_status(philo, "has taken a fork", dead);
		if (*dead)
			unlock_forks(philo->myfork, philo->leftfork);
		return ;
	}
	pthread_mutex_lock(philo->myfork);
	print_status(philo, "has taken a fork", dead);
	if (*dead)
		return (unlock_forks(philo->myfork, NULL));
	pthread_mutex_lock(philo->leftfork);
	print_status(philo, "has taken a fork", dead);
	if (*dead)
		unlock_forks(philo->myfork, philo->leftfork);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:49:31 by macampos          #+#    #+#             */
/*   Updated: 2024/03/31 20:53:16 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef unsigned long long		t_time;

typedef struct s_philosopher	t_philosopher;

typedef struct s_table
{
	int				philosophers;
	int				meals;
	int				dead;
	t_time			time_to_eat;
	t_time			time_to_sleep;
	t_time			time_to_die;
	t_time			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	monitoring;
	t_philosopher	*firstphilo;
}					t_table;

typedef struct s_philosopher
{
	t_time			last_meal;
	pthread_mutex_t	*myfork;
	pthread_mutex_t	*leftfork;
	int				dead;
	int				id;
	int				mealseaten;
	t_table			*table;
	pthread_t		thread;
	t_philosopher	*next;
}					t_philosopher;

t_philosopher	*free_philos(t_table *table);
void			*join_routines(t_table *table);
void			print_status(t_philosopher *philo, char *status, int *dead);
void			routine_start(t_table *table);
int				ft_atoi(const char *str);
void			*philo_function(void *philo);
void			_usleep(t_time time);
t_time			get_time(void);
t_philosopher	*initiate_philos(t_table *table);
void			*observe(t_table *table);
void			take_forks(t_philosopher *philo, int *dead);
void			unlock_forks(pthread_mutex_t *myfork,
					pthread_mutex_t *leftfork);
int				is_valid_number(char *str);
int				ft_strlen(char *c);

#endif
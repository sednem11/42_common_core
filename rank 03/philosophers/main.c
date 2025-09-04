/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macampos <macampos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:18:47 by macampos          #+#    #+#             */
/*   Updated: 2024/04/01 16:35:29 by macampos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Wrong number of arguments\n"));
	if (!is_valid_number(argv[1]) || !is_valid_number(argv[2])
		|| !is_valid_number(argv[3]) || !is_valid_number(argv[4]))
		return (printf("Invalid argument\n"));
	if (argc == 6 && !is_valid_number(argv[5]))
		return (printf("Invalid argument\n"));
	if (ft_atoi(argv[1]) < 1)
		return (printf("Invalid number of philosophers\n"));
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (printf("Invalid time\n"));
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (printf("Invalid number of meals\n"));
	if (ft_strlen(argv[2]) > 11)
		return (printf("Invalid time\n"));
	return (0);
}

void	initiate_values(t_table *table, int argc, char **argv)
{
	table->philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->meals = ft_atoi(argv[5]);
	else
		table->meals = -1;
	table->start_time = get_time();
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philosophers);
	table->firstphilo = initiate_philos(table);
	table->dead = 0;
}

void	init_mutexes(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->philosophers)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->write, NULL);
	pthread_mutex_init(&table->monitoring, NULL);
}

void	destroy_main(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philosophers)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	pthread_mutex_destroy(&table->write);
	pthread_mutex_destroy(&table->monitoring);
}

int	main(int argc, char **argv)
{
	struct s_table	table;

	if (parse_args(argc, argv))
		return (1);
	initiate_values(&table, argc, argv);
	init_mutexes(&table);
	routine_start(&table);
	observe(&table);
	join_routines(&table);
	free_philos(&table);
	destroy_main(&table);
	return (0);
}

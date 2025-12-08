/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:40:07 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/09/25 18:49:31 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	data->nb_philos = ft_atoi(argv[0]);
	data->time_to_die = ft_atoi(argv[1]);
	data->time_to_eat = ft_atoi(argv[2]);
	data->time_to_sleep = ft_atoi(argv[3]);
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[4]);
	else
		data->must_eat_count = -1;
	data->start_time = 0;
	data->simulation_end = 0;
	data->philosophers_eating_started = 0;
	data->philos = NULL;
	data->forks = NULL;
	return (1);
}

static int	init_fork_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
	{
		write(2, "Error: Failed to allocate memory for fork mutexes\n", 51);
		return (0);
	}
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			write(2, "Error: Failed to Initialize fork mutex\n", 40);
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			free(data->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_other_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		write(2, "Error: Failed to initialize print mutex\n", 41);
		cleanup_mutexes(data);
		return (0);
	}
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
	{
		write(2, "Error: Failed to initialize meal mutex\n", 40);
		cleanup_mutexes(data);
		return (0);
	}
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		write(2, "Error: Failed to initialize death mutex\n", 41);
		cleanup_mutexes(data);
		return (0);
	}
	return (1);
}

int	init_mutexes(t_data *data)
{
	if (!init_fork_mutexes(data))
		return (0);
	if (!init_other_mutexes(data))
		return (0);
	return (1);
}

void	cleanup_mutexes(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->death_mutex);
}

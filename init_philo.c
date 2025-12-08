/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:53:07 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/09/25 16:42:44 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_eat_limit(t_philo *philo)
{
	int	should_stop;

	should_stop = 0;
	if (philo->data->must_eat_count != -1)
	{
		pthread_mutex_lock(&philo->data->meal_mutex);
		if (philo->times_eaten >= philo->data->must_eat_count)
			should_stop = 1;
		pthread_mutex_unlock(&philo->data->meal_mutex);
	}
	return (should_stop);
}

void	start_philo_cycle(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		take_forks(philo);
		if (!check_simulation_end(philo))
			eat(philo);
		sleep_philo(philo);
	}
}

void	*philos_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philos == 1)
		return (handle_single_philo(philo), NULL);
	start_philo_cycle(philo);
	while (!check_simulation_end(philo))
	{
		if (check_eat_limit(philo))
			break ;
		think(philo);
		take_forks(philo);
		if (check_simulation_end(philo))
			return (release_forks(philo), NULL);
		eat(philo);
		sleep_philo(philo);
	}
	return (NULL);
}

static void	init_philos_meal_time(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		i++;
	}
}

int	start_simulation(t_data *data)
{
	if (!allocate_and_init_philos(data))
		return (0);
	if (!init_mutexes(data))
	{
		free(data->philos);
		return (0);
	}
	data->start_time = get_time();
	data->simulation_end = 0;
	data->someone_died = 0;
	data->all_ate_enough = 0;
	init_philos_meal_time(data);
	if (!create_death_monitor(data))
		return (0);
	if (!create_all_threads(data))
		return (cleanup_failed_simulation(data));
	if (!join_all_threads(data))
		return (cleanup_failed_simulation(data));
	pthread_join(data->death_thread, NULL);
	if (data->someone_died)
		return (cleanup_failed_simulation(data));
	return (cleanup_successful_simulation(data));
}

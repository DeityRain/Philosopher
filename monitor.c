/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 08:11:08 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/10/07 08:52:46 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_death_monitor(t_data *data)
{
	if (pthread_create(&data->death_thread, NULL, death_monitor, data))
	{
		write(2, "Error: Failed to create death monitoring thread\n", 49);
		cleanup_mutexes(data);
		free(data->philos);
		return (0);
	}
	return (1);
}

static int	check_philosopher_death(t_data *data, int i)
{
	long	current_time;
	long	time_since_last_meal;

	current_time = get_time();
	pthread_mutex_lock(&data->meal_mutex);
	time_since_last_meal = current_time - data->philos[i].last_meal_time;
	pthread_mutex_unlock(&data->meal_mutex);
	if (time_since_last_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->simulation_end = 1;
		data->someone_died = 1;
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d died\n", current_time - data->start_time,
			data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	return (0);
}

void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d has taken a fork\n", get_time() - philo->data->start_time,
		philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_die * 1000);
}

static void	end_simulation_success(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->simulation_end = 1;
	pthread_mutex_unlock(&data->death_mutex);
}

void	*death_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->simulation_end && (pthread_mutex_unlock(&data->death_mutex)))
			break ;
		pthread_mutex_unlock(&data->death_mutex);
		check_all_ate_enough(data);
		if (data->all_ate_enough && (end_simulation_success(data), 1))
			break ;
		i = -1;
		while (++i < data->nb_philos)
			if (check_philosopher_death(data, i))
				return (NULL);
		usleep(1000);
	}
	return (NULL);
}

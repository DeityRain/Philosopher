/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 08:14:57 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/09/25 11:19:34 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	stop_death_monitor(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->simulation_end = 1;
	pthread_mutex_unlock(&data->death_mutex);
	pthread_join(data->death_thread, NULL);
}

static void	free_resources(t_data *data)
{
	cleanup_mutexes(data);
	free(data->philos);
}

int	cleanup_failed_simulation(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->simulation_end = 1;
	pthread_mutex_unlock(&data->death_mutex);
	pthread_join(data->death_thread, NULL);
	free_resources(data);
	return (0);
}

int	cleanup_successful_simulation(t_data *data)
{
	stop_death_monitor(data);
	free_resources(data);
	return (1);
}

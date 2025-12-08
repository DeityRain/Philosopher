/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 08:10:26 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/09/25 18:52:00 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	update_meal_info(t_philo *philo, long current_time)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = current_time;
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
}

void	eat(t_philo *philo)
{
	long	current_time;

	if (check_simulation_end(philo))
	{
		release_forks(philo);
		return ;
	}
	current_time = get_time();
	update_meal_info(philo, current_time);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!check_simulation_end(philo))
		printf("%ld %d is eating\n", current_time - philo->data->start_time,
			philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->time_to_eat * 1000);
	release_forks(philo);
}

void	think(t_philo *philo)
{
	long	current_time;
	long	think_time;

	if (check_simulation_end(philo))
		return ;
	current_time = get_time();
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!check_simulation_end(philo))
		printf("%ld %d is thinking\n", current_time - philo->data->start_time,
			philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	think_time = (philo->data->time_to_die - philo->data->time_to_eat
			- philo->data->time_to_sleep) / 2;
	if (think_time > 0)
		usleep(think_time * 1000);
}

void	sleep_philo(t_philo *philo)
{
	long	time_since_last_meal;
	long	time_to_die;
	long	time_to_sleep;
	long	sleep_time;

	time_to_die = philo->data->time_to_die;
	time_to_sleep = philo->data->time_to_sleep;
	pthread_mutex_lock(&philo->data->meal_mutex);
	time_since_last_meal = get_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if (time_to_die - time_since_last_meal < time_to_sleep)
		sleep_time = time_to_die - time_since_last_meal;
	else
		sleep_time = time_to_sleep;
	if (sleep_time > 0)
		usleep(sleep_time * 1000);
}

void	check_all_ate_enough(t_data *data)
{
	int	i;
	int	all_ate_enough;

	if (data->must_eat_count == -1)
		return ;
	all_ate_enough = 1;
	pthread_mutex_lock(&data->meal_mutex);
	i = 0;
	while (i < data->nb_philos)
	{
		if (data->philos[i].times_eaten < data->must_eat_count)
		{
			all_ate_enough = 0;
			break ;
		}
		i++;
	}
	if (all_ate_enough)
		data->all_ate_enough = 1;
	pthread_mutex_unlock(&data->meal_mutex);
}

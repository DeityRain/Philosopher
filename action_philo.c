/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:49:30 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/09/26 03:01:28 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_first_fork(t_philo *philo, int fork)
{
	long	current_time;

	pthread_mutex_lock(&philo->data->forks[fork]);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!check_simulation_end(philo))
	{
		current_time = get_time();
		printf("%ld %d has taken a fork\n", current_time
			- philo->data->start_time, philo->id);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	take_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (philo->data->nb_philos == 1)
	{
		take_first_fork(philo, philo->left_fork);
		usleep(philo->data->time_to_die * 1000);
		return ;
	}
	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	take_first_fork(philo, first_fork);
	take_first_fork(philo, second_fork);
}

void	release_forks(t_philo *philo)
{
	if (philo->data->nb_philos > 1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	}
}

int	check_simulation_end(t_philo *philo)
{
	int	should_end;

	pthread_mutex_lock(&philo->data->death_mutex);
	should_end = philo->data->simulation_end;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (should_end);
}

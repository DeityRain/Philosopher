/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 08:11:55 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/09/25 16:46:42 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	initialize_single_philo(t_data *data, int i)
{
	data->philos[i].id = i + 1;
	data->philos[i].times_eaten = 0;
	data->philos[i].last_meal_time = get_time();
	data->philos[i].left_fork = i;
	data->philos[i].right_fork = (i + 1) % data->nb_philos;
	data->philos[i].first_iteration = 1;
	data->philos[i].data = data;
}

int	allocate_and_init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
	{
		write(2, "Error: Failed to allocate memory for philosophere\n", 50);
		return (0);
	}
	i = 0;
	while (i < data->nb_philos)
	{
		initialize_single_philo(data, i);
		i++;
	}
	return (1);
}

int	create_all_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philos_routine,
				&data->philos[i]) != 0)
		{
			write(2, "Error: Failed to create philosopher thread\n", 44);
			return (0);
		}
		i++;
	}
	return (1);
}

int	join_all_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			write(2, "Error: Failed to join philosopher thread\n", 42);
			return (0);
		}
		i++;
	}
	return (1);
}

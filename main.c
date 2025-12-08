/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 08:04:45 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/10/06 07:56:55 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//  ./philo [number_of_philo] [time_to_die] [time_to_eat] [time_to_sleep]
//[number_of_times_each_philosopher_must_eat]
// ./philo 4 410 200 200
// ./philo 5 800 200 200 5
// ./philo 2 300 100 100 2
// some edge cases to test for Breaking the programm.
// ./philo 1 800 200 200
// ./philo 200 800 200 200
// ./philo 4 100 200 100
// ./philo 4 100 100 200
// ./philo 4 0 200 200
// ./philo 4 -800 200 200
// ./philo 4 800 200 200 0
// ./philo 4 800 200 200 -5

int	valid_optional_args(char *argv5)
{
	if (!all_numbers(argv5))
	{
		write(2, "\nYour number of must eat should be only number(s).\n\n", 53);
		return (0);
	}
	return (1);
}

int	valid_required_args(char *argv1, char *argv2, char *argv3, char *argv4)
{
	if (!all_numbers(argv1))
	{
		write(2, "\nYour number of philo should be only number(s).\n\n", 49);
		return (0);
	}
	if (!all_numbers(argv2))
	{
		write(2, "\nYour time to die should be only number(s).\n\n", 46);
		return (0);
	}
	if (!all_numbers(argv3))
	{
		write(2, "\nYour time to eat should be only number(s).\n\n", 46);
		return (0);
	}
	if (!all_numbers(argv4))
	{
		write(2, "\nYour time to sleep should be only number(s).\n\n", 48);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc == 5 || argc == 6)
	{
		i = 1;
		while (i < argc)
		{
			if (all_numbers(argv[i]))
				i++;
			else
				return (write(2, "\nError: Invalid Arguments\n\n", 28),
					1);
		}
		init_data(&data, argc, &argv[1]);
		if (data.time_to_die <= 0 || data.time_to_eat <= 0
			|| data.time_to_sleep <= 0)
			return (write(2, "\nError: Times must be positive\n\n", 33), 1);
		if (!start_simulation(&data))
			return (write(2, "\nError: Simulation failed\n\n", 28), 1);
		return (0);
	}
	else
		return (write(2, "\nError: Wrong amount of Arguments.\n\n", 36), 0);
}

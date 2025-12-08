/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 08:54:46 by qdeffaux          #+#    #+#             */
/*   Updated: 2025/09/25 18:45:43 by qdeffaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* ************************************************************************** */
/*                               STRUCTURES                                   */
/* ************************************************************************** */

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	long			last_meal_time;
	int				left_fork;
	int				right_fork;
	int				first_iteration;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				simulation_end;
	int				philosophers_eating_started;
	int				someone_died;
	int				all_ate_enough;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
	pthread_t		death_thread;
	t_philo			*philos;
}					t_data;

/* ************************************************************************** */
/*                                  UTILS.C                                  */
/* ************************************************************************** */

int					all_numbers(char *str);
long				get_time(void);
int					ft_isspace(int c);
int					handle_overflow(int sign);
int					ft_atoi(const char *str);

/* ************************************************************************** */
/*                              INIT_PHILO.C                                  */
/* ************************************************************************** */

void				*philos_routine(void *arg);
int					start_simulation(t_data *data);

/* ************************************************************************** */
/*                              INIT_HELPER.C                                 */
/* ************************************************************************** */

int					allocate_and_init_philos(t_data *data);
int					create_all_threads(t_data *data);
int					join_all_threads(t_data *data);

/* ************************************************************************** */
/*                              SETUP_PHILO.C                                 */
/* ************************************************************************** */

int					init_data(t_data *data, int argc, char **argv);
int					init_mutexes(t_data *data);
void				cleanup_mutexes(t_data *data);

/* ************************************************************************** */
/*                             ACTION_PHILO.C                                 */
/* ************************************************************************** */

void				take_forks(t_philo *philos);
void				release_forks(t_philo *philo);
int					check_simulation_end(t_philo *philo);

/* ************************************************************************** */
/*                             ACTION_PHILO2.C                                */
/* ************************************************************************** */

void				eat(t_philo *philo);
void				think(t_philo *philo);
void				sleep_philo(t_philo *philo);
void				check_all_ate_enough(t_data *data);

/* ************************************************************************** */
/*                                MONITOR.C                                   */
/* ************************************************************************** */

int					create_death_monitor(t_data *data);
void				handle_single_philo(t_philo *philo);
void				*death_monitor(void *arg);

/* ************************************************************************** */
/*                                CLEANUP.C                                   */
/* ************************************************************************** */

int					cleanup_failed_simulation(t_data *data);
int					cleanup_successful_simulation(t_data *data);

#endif

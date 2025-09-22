/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:15:04 by moaljazz          #+#    #+#             */
/*   Updated: 2025/09/15 18:59:36 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_PHILOS 250
# define STR_MAX_PHILOS "250"

# ifndef DEBUG_FORMATTING
#  define DEBUG_FORMATTING 0
# endif

# define PHILO_PROG_NAME "philo:"
# define PHILO_USAGE \
	"%s usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define PHILO_ERR_INPUT_DIGIT \
	"%s invalid input: %s: \
not a valid unsigned integer between 0 and 2147483647.\n"
# define PHILO_ERR_INPUT_POFLOW \
	"%s invalid input: \
there must be between 1 and %s philosophers.\n"
# define PHILO_ERR_THREAD "%s error: Could not create thread.\n"
# define PHILO_ERR_MALLOC "%s error: Could not allocate memory.\n"
# define PHILO_ERR_MUTEX "%s error: Could not create mutex.\n"

typedef struct s_philo	t_philo;

typedef struct s_table
{
	time_t				start_time;
	unsigned int		nb_philos;
	pthread_t			gcs;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					must_eat_num;
	bool				sim_stop;
	pthread_mutex_t		sim_stop_lock;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		*fork_locks;
	t_philo				**philos;
}						t_table;

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		times_ate;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
	time_t				last_meal;
	t_table				*table;
}						t_philo;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}						t_status;

bool					valid_input(int ac, char **av);
int						ft_atoi(char *str);
t_table					*initialize_table(int ac, char **av, int i);
void					*philosopher(void *data);
time_t					get_time_ms(void);
void					philo_sleep(t_table *table, time_t sleep_time);
void					start_delay(time_t start_time);
void					write_sts(t_philo *philo, bool reaper, t_status status);
void					philo_assign(t_philo **philos, t_table *table,
							unsigned int i);

void					write_out(t_table *table);
void					*err_null(char *str, char *details, t_table *table);
int						msg(char *str, char *detail, int exit_no);
void					*gcs(void *data);
bool					is_simulation_stopped(t_table *table);
int						err_fail(char *str, char *details, t_table *table);
void					*free_table(t_table *table);
void					destroy_mutx(t_table *table);
void					assign_forks(t_philo *philo);
void					write_print_state(t_status status, t_philo *philo);
void					print_status(t_philo *philo, char *str);

#endif

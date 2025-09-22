/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:51:01 by moaljazz          #+#    #+#             */
/*   Updated: 2025/09/15 19:51:06 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_status_debug(t_philo *philo, char *str, t_status status)
{
	long	timestamp;

	timestamp = get_time_ms() - philo->table->start_time;
	if (status == GOT_FORK_1)
		printf("[%10ld]\t%03d\t%s: fork [%d]\n", timestamp, philo->id + 1, str,
			philo->fork[0]);
	else if (status == GOT_FORK_2)
		printf("[%10ld]\t%03d\t%s: fork [%d]\n", timestamp, philo->id + 1, str,
			philo->fork[1]);
	else
		printf("[%10ld]\t%03d\t%s\n", timestamp, philo->id + 1, str);
}

void	write_status_debug(t_philo *philo, t_status status)
{
	if (status == DIED)
		print_status_debug(philo, "died", status);
	else if (status == EATING)
		print_status_debug(philo, "is eating", status);
	else if (status == SLEEPING)
		print_status_debug(philo, "is sleeping", status);
	else if (status == THINKING)
		print_status_debug(philo, "is thinking", status);
	else if (status == GOT_FORK_1 || status == GOT_FORK_2)
		print_status_debug(philo, "has taken a fork", status);
}

void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time_ms() - philo->table->start_time, philo->id
		+ 1, str);
}

void	write_sts(t_philo *philo, bool reaper_report, t_status status)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (is_simulation_stopped(philo->table) && !reaper_report)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	if (DEBUG_FORMATTING)
	{
		write_status_debug(philo, status);
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	write_print_state(status, philo);
	pthread_mutex_unlock(&philo->table->write_lock);
}

void	write_out(t_table *table)
{
	unsigned int	i;
	unsigned int	full_count;

	i = 0;
	full_count = 0;
	i = 0;
	while (i < table->nb_philos)
	{
		if (table->philos[i++]->times_ate >= (unsigned int)table->must_eat_num)
			full_count++;
	}
	pthread_mutex_lock(&table->write_lock);
	printf("%d/%d philosophers had at least %d meals.\n", full_count,
		table->nb_philos, table->must_eat_num);
	pthread_mutex_unlock(&table->write_lock);
}

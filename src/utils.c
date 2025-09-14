/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:19:05 by moaljazz          #+#    #+#             */
/*   Updated: 2025/09/04 19:19:08 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void eat_sleep_routine(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
    write_sts(philo, false, GOT_FORK_1);
    pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
    write_sts(philo, false, GOT_FORK_2);
    write_sts(philo, false, EATING);

    pthread_mutex_lock(&philo->meal_time_lock);
    philo->last_meal = get_time_ms();
    pthread_mutex_unlock(&philo->meal_time_lock);

    philo_sleep(philo->table, philo->table->time_to_eat);

    if (!is_simulation_stopped(philo->table))
    {
        pthread_mutex_lock(&philo->meal_time_lock);
        philo->times_ate += 1;
        pthread_mutex_unlock(&philo->meal_time_lock);
    }

    write_sts(philo, false, SLEEPING);
    pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);
    pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
    philo_sleep(philo->table, philo->table->time_to_sleep);
}

static void think_routine(t_philo *philo, bool silent)
{
    time_t time_to_think;

    pthread_mutex_lock(&philo->meal_time_lock);
    time_to_think = (philo->table->time_to_die
        - (get_time_ms() - philo->last_meal)
        - philo->table->time_to_eat) / 2;
    pthread_mutex_unlock(&philo->meal_time_lock);

    if (time_to_think < 0)
        time_to_think = 0;
    if (time_to_think == 0 && silent)
        time_to_think = 1;
    if (time_to_think > 600)
        time_to_think = 200;
    if (!silent)
        write_sts(philo, false, THINKING);
    philo_sleep(philo->table, time_to_think);
}

static void *lone_philo_routine(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
    write_sts(philo, false, GOT_FORK_1);
    philo_sleep(philo->table, philo->table->time_to_die);
    write_sts(philo, false, DIED);
    pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
    return NULL;
}

void *philosopher(void *data)
{
    t_philo *philo = (t_philo *)data;

    if (philo->table->must_eat_num == 0)
        return NULL;

    pthread_mutex_lock(&philo->meal_time_lock);
    philo->last_meal = philo->table->start_time;
    pthread_mutex_unlock(&philo->meal_time_lock);

    start_delay(philo->table->start_time);

    if (philo->table->time_to_die == 0)
        return NULL;
    if (philo->table->nb_philos == 1)
        return lone_philo_routine(philo);
    else if (philo->id % 2)
        think_routine(philo, true);

    while (!is_simulation_stopped(philo->table))
    {
        eat_sleep_routine(philo);
        think_routine(philo, false);
    }
    return NULL;
}
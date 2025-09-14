/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:17:57 by moaljazz          #+#    #+#             */
/*   Updated: 2025/09/04 19:18:00 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void set_sim_stop_flag(t_table *table, bool state)
{
    pthread_mutex_lock(&table->sim_stop_lock);
    table->sim_stop = state;
    pthread_mutex_unlock(&table->sim_stop_lock);
}

bool is_simulation_stopped(t_table *table)
{
    bool stopped = false;

    pthread_mutex_lock(&table->sim_stop_lock);
    if (table->sim_stop)
        stopped = true;
    pthread_mutex_unlock(&table->sim_stop_lock);
    return stopped;
}

static bool kill_philo(t_philo *philo)
{
    time_t now = get_time_ms();

    if ((now - philo->last_meal) >= philo->table->time_to_die)
    {
        set_sim_stop_flag(philo->table, true);
        write_sts(philo, true, DIED);
        pthread_mutex_unlock(&philo->meal_time_lock);
        return true;
    }
    return false;
}

static bool end_condition_reached(t_table *table)
{
    unsigned int i = 0;
    bool all_ate_enough = true;

    while (i < table->nb_philos)
    {
        pthread_mutex_lock(&table->philos[i]->meal_time_lock);
        if (kill_philo(table->philos[i]))
            return true;
        if (table->must_eat_num != -1)
        {
            if (table->philos[i]->times_ate < (unsigned int)table->must_eat_num)
                all_ate_enough = false;
        }
        pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
        i++;
    }
    if (table->must_eat_num != -1 && all_ate_enough)
    {
        set_sim_stop_flag(table, true);
        return true;
    }
    return false;
}

void *gcs(void *data)
{
    t_table *table = (t_table *)data;

    if (table->must_eat_num == 0)
        return NULL;
    set_sim_stop_flag(table, false);
    start_delay(table->start_time);
    while (true)
    {
        if (end_condition_reached(table))
            return NULL;
        usleep(1000);
    }
    return NULL;
}
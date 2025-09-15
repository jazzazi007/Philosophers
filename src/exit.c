/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:57:33 by moaljazz          #+#    #+#             */
/*   Updated: 2025/09/15 18:57:38 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*free_table(t_table *table)
{
	unsigned int	i;

	if (!table)
		return (NULL);
	if (table->fork_locks)
		free(table->fork_locks);
	if (table->philos)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			if (table->philos[i])
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
	free(table);
	return (NULL);
}

void	destroy_mutx(t_table *table)
{
	unsigned int	i;

	if (!table)
		return ;
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->fork_locks[i]);
		pthread_mutex_destroy(&table->philos[i++]->meal_time_lock);
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->sim_stop_lock);
}

int	msg(char *str, char *detail, int exit_no)
{
	if (!detail)
		printf(str, STR_PROG_NAME);
	else
		printf(str, STR_PROG_NAME, detail);
	return (exit_no);
}

int	err_fail(char *str, char *details, t_table *table)
{
	if (table)
		free_table(table);
	return (msg(str, details, 0));
}

void	*err_null(char *str, char *details, t_table *table)
{
	if (table)
		free_table(table);
	msg(str, details, EXIT_FAILURE);
	return (NULL);
}

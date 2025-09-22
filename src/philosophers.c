/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 18:58:41 by moaljazz          #+#    #+#             */
/*   Updated: 2025/09/15 18:58:44 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	start_simulation(t_table *table)
{
	unsigned int	i;

	i = 0;
	table->start_time = get_time_ms() + (table->nb_philos * 20);
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL, philosopher,
				table->philos[i]) != 0)
			return (err_fail(PHILO_ERR_THREAD, NULL, table));
		i++;
	}
	if (table->nb_philos > 1)
	{
		if (pthread_create(&table->gcs, NULL, gcs, table) != 0)
			return (err_fail(PHILO_ERR_THREAD, NULL, table));
	}
	return (true);
}

void	stop_simulation(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	if (table->nb_philos > 1)
		pthread_join(table->gcs, NULL);
	if (DEBUG_FORMATTING && table->must_eat_num != -1)
		write_out(table);
	destroy_mutx(table);
	free_table(table);
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if (ac - 1 < 4 || ac - 1 > 5)
		return (msg(PHILO_USAGE, NULL, EXIT_FAILURE));
	if (!valid_input(ac, av))
		return (EXIT_FAILURE);
	table = initialize_table(ac, av, 1);
	if (!table)
		return (EXIT_FAILURE);
	if (!start_simulation(table))
		return (EXIT_FAILURE);
	stop_simulation(table);
	return (EXIT_SUCCESS);
}

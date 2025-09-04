/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:18:39 by moaljazz          #+#    #+#             */
/*   Updated: 2025/09/04 19:18:42 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_philos(t_engine *en, t_philo *philos, t_mutex *forks, char **argv)
{
	int	i;
	int	philo_count;

	if (!en || !philos || !forks || !argv)
		return;

	philo_count = ft_atoi(argv[1]);
	i = -1;
	while (++i < philo_count)
	{
		philos[i] = (t_philo){0}; // Zero initialize structure
		philos[i].id = i + 1;
		philos[i].times.die = ft_atoi(argv[2]);
		philos[i].times.eat = ft_atoi(argv[3]);
		philos[i].times.sleep = ft_atoi(argv[4]);
		philos[i].times.last_meal = get_current_time();
		philos[i].times.born_time = get_current_time();
		philos[i].must_eat = argv[5] ? ft_atoi(argv[5]) : -1;
		philos[i].philo_count = philo_count;

		// Fork assignment with boundary checking
		philos[i].mutexes.left_fork = &forks[i];
		philos[i].mutexes.right_fork = &forks[(i + 1) % philo_count];
		philos[i].mutexes.write_lock = &en->write_lock;
		philos[i].mutexes.meal_lock = &en->meal_lock;
	}
}

void	init_forks(t_engine *engine, t_mutex *forks, int count)
{
	int	i;

	if (!engine || !forks || count <= 0)
		return;

	for (i = 0; i < count; i++)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			destroy_all(engine, "[Mutex Init ERROR]\n", i, 1);
			return;
		}
	}
}

void	init_engine(t_engine *engine, t_philo *philos, t_mutex *forks)
{
	engine->forks = forks;
	engine->philos = philos;
	if (pthread_mutex_init(&engine->write_lock, NULL) != 0
		|| pthread_mutex_init(&engine->meal_lock, NULL) != 0)
		destroy_all(engine, "[Mutex Init ERROR]\n", -1, 1);
}

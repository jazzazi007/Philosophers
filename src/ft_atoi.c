/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:18:15 by moaljazz          #+#    #+#             */
/*   Updated: 2025/09/15 18:57:54 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philo_assign(t_philo **philos, t_table *table, unsigned int i)
{
	philos[i]->table = table;
	philos[i]->id = i;
	philos[i]->times_ate = 0;
	philos[i]->last_meal = get_time_ms();
	assign_forks(philos[i]);
}

bool	is_digits_only(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	ft_atoi(char *str)
{
	unsigned long long	nb;
	int					i;

	nb = 0;
	i = 0;
	if (!str)
		return (-1);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		return (-1);
	return ((int)nb);
}

bool	valid_input(int ac, char **av)
{
	int	i;
	int	nb;

	i = 1;
	while (i < ac)
	{
		if (!is_digits_only(av[i]))
			return (msg(PHILO_ERR_INPUT_DIGIT, av[i], false));
		nb = ft_atoi(av[i]);
		if (i == 1 && (nb <= 0 || nb > MAX_PHILOS))
			return (msg(PHILO_ERR_INPUT_POFLOW, STR_MAX_PHILOS, false));
		if (i != 1 && nb == -1)
			return (msg(PHILO_ERR_INPUT_DIGIT, av[i], false));
		i++;
	}
	return (true);
}

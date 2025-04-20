#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philo
{
    int		id;
    int		time_to_eat;
    int		time_to_sleep;
    int		time_to_die;
    int		num_of_philosophers;
    int		num_of_times_must_eat;
}	t_philo;

int	ft_atoi(const char *str);

#endif

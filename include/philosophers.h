#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

typedef struct s_philo
{
    int		id;
    int		time_to_eat;
    int		time_to_sleep;
    int		time_to_die;
    int		num_of_philosophers;
    int		num_of_times_must_eat;
    int     print;
    int     *forks;
}	t_philo;



typedef struct s_data
{
    t_philo    *philos;
    pthread_t   *threads;
    pthread_mutex_t mutex;
} t_data;

int init_philos(t_data *data);
int	ft_atoi(const char *str);
int init_mutex(t_data *data);
int	ft_isdigit(int c);
void eating(t_data *data);
void sleeping(t_data *data);
void thinking(t_data *data);
void died(t_data *data);
void forks(t_data *data);
int get_time(void);
int mutex_destroy(t_data *data);


#endif

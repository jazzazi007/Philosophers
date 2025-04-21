#include "../include/philosophers.h"

void eating(t_data *data)
{
    printf("Philosopher %d is eating\n", data->philos->id);
    usleep(data->philos->time_to_eat * 1000);
}

void sleeping(t_data *data)
{
    printf("Philosopher %d is sleeping\n", data->philos->id);
    usleep(data->philos->time_to_sleep * 1000);
}

void thinking(t_data *data)
{
    printf("Philosopher %d is thinking\n", data->philos->id);
    usleep(data->philos->time_to_eat * 1000);
}

void died(t_data *data)
{
    printf("Philosopher %d has died\n", data->philos->id);
}
void forks(t_data *data)
{
    printf("Philosopher %d has taken a fork\n", data->philos->id);
}

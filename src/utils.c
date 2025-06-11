#include "../include/philosophers.h"

void forks_init(t_philo *philos)
{
    int i;

    philos->forks = (int *) malloc(sizeof(int) * philos->num_of_philosophers);
    if (!philos->forks)
    {
        printf("Error: Forks allocation failed\n");
        exit(1);
    }
    i = 0;
    while (i < philos->num_of_philosophers)
    {
        printf("Forks[%d] initialized\n", i);
        philos->forks[i++] = 0;
    }
}

void process_philo(t_data *data)
{
    t_philo *philo = data->philos;

    pthread_mutex_lock(&data->mutex);
    printf("Philosopher %d is eating\n", philo->id);
    usleep(philo->time_to_eat * 1000); // Simulate eating time
    pthread_mutex_unlock(&data->mutex);
    printf("Philosopher %d finished eating\n", philo->id);
    usleep(philo->time_to_sleep * 1000); // Simulate sleeping time
    printf("Philosopher %d is thinking\n", philo->id);
    usleep(philo->time_to_sleep * 1000); // Simulate thinking time
}
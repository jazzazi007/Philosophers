#include "../include/philosophers.h"

void* philo_active(void *arg) {
    t_data *data = (t_data *)arg;
    t_philo *philos = data->philos;
    //int num_of_philosophers = philos->num_of_philosophers;
    while(1) {
        pthread_mutex_lock(&data->mutex);
        printf("Thread 1 is running...\n");
        printf("philo %d\n", philos->id);
        pthread_mutex_unlock(&data->mutex);
        sleep(1);
    }
    return NULL;
}

int init_mutex(t_data *data)
{
    if (pthread_mutex_init(&data->mutex, NULL) != 0)
    {
        printf("Error: Mutex initialization failed\n");
        return (1);
    }
    return (0);
}

int mutex_destroy(t_data *data)
{
    if (pthread_mutex_destroy(&data->mutex) != 0)
    {
        printf("Error: Mutex destruction failed\n");
        return (1);
    }
    printf("Mutex destroyed successfully\n");
    return (0);
}

int init_philos(t_data *data)
{
    int i;

    i = 0;
    data->threads = malloc(sizeof(pthread_t) * data->philos->num_of_philosophers);
    if (!data->threads)
        return (1);
    forks_init(data->philos); // Initialize forks for each philosopher
    while(i < data->philos->num_of_philosophers)
    {
        if (pthread_create(&data->threads[i], NULL, philo_active, data) != 0)
        {
            free(data->threads);
            return (1);
        }
        printf("Philosopher %d created\n", i);
        printf("i ID: %d\n", i);
        i++;
    }
    return (0);
}

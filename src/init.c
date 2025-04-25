#include "../include/philosophers.h"

void* myThreadFunc(void *arg) {
    t_data *data = (t_data *)arg;
    t_philo *philos = data->philos;
    //int num_of_philosophers = philos->num_of_philosophers;
    while(1) {
        printf("Thread 1 is running...\n");
        printf("philo %d\n", philos->id);
        sleep(1);
    }
    return NULL;
}

void* myThreadFunc2(void *arg) {
    t_data *data = (t_data *)arg;
    t_philo *philos = data->philos;
   // int num_of_philosophers = philos->num_of_philosophers;
    while(1) {
        printf("Thread 2 is running...\n");
        printf("philo %d\n", philos->id);
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
    pthread_t *threads;
    int i;

    i = 0;
    threads = malloc(sizeof(pthread_t) * data->philos->num_of_philosophers);
    if (!threads)
        return (1);
    while(i < data->philos->num_of_philosophers)
    {
        if (i % 2 == 0)
        {
            if (pthread_create(&threads[i], NULL, myThreadFunc, data) != 0)
            {
                free(threads);
                return (1);
            }
        }
        else
        {
            if (pthread_create(&threads[i], NULL, myThreadFunc2, data) != 0)
            {
                free(threads);
                return (1);
            }
        }
        printf("Philosopher %d created\n", i);
        printf("i ID: %d\n", i);
        i++;
    }
    return (0);
}

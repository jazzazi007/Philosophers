#include "../include/philosophers.h"

void* myThreadFunc() {
    while(1) {
        printf("Thread is running...\n");
        sleep(1);
    }
    return NULL;
}

int create_philos(t_philo *philos)
{
    pthread_t *threads;
    int i;

    i = 0;
    threads = malloc(sizeof(pthread_t) * philos->num_of_philosophers);
    if (!threads)
        return (1);
    while(i < philos->num_of_philosophers)
    {
        if (pthread_create(&threads[i], NULL, myThreadFunc, NULL) != 0)
        {
            free(threads);
            return (1);
        }
        printf("Philosopher %d created\n", i);
        i++;
    }
    return (0);
}

int main(int ac, char **av)
{
    t_philo philos;
    t_data data;

    memset(&philos, 0, sizeof(t_philo));
    if (ac != 5 && ac != 6)
    {
        printf("Error: Wrong number of arguments\n");
        return (1);
    }
    philos.num_of_philosophers = ft_atoi(av[1]);
    philos.time_to_die = ft_atoi(av[2]);
    philos.time_to_eat = ft_atoi(av[3]);
    philos.time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
    {
        philos.num_of_times_must_eat = ft_atoi(av[5]);
        if (philos.num_of_times_must_eat <= 0)
        {
            printf("Error: Number of philosophers must be positive\n");
            return (1);
        }
    }
    else
        philos.num_of_times_must_eat = -1;
    if (init_mutex(data) != 0)
        return (1);
    data.philos = &philos;
    printf("create return %d\n",create_philos(&philos));
    printf("Number of philosophers: %d\n", philos.num_of_philosophers);
}

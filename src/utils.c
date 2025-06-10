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
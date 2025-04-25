#include "../include/philosophers.h"

int main(int ac, char **av)
{
    t_philo philos;
    t_data data;
    int i = 1;
    int j = 0;

    memset(&philos, 0, sizeof(philos));
    memset(&data, 0, sizeof(data));
    while (av[++i])
    {
        j = 0;
        while (av[i][j])
        {
            if (ft_isdigit(av[i][j++]) == 0)
            {
                printf("Error: Argument is not a number\n");
                return (1);
            }
        }
    }
    if (ac != 5 && ac != 6)
    {
        printf("Error: Wrong number of arguments\n");
        return (1);
    }
    philos.num_of_philosophers = ft_atoi(av[1]);
    printf("philos.num_of_philosophers = %d\n", philos.num_of_philosophers);
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
    if (init_mutex(&data) != 0)
        return (1);
    data.philos = &philos;
    printf("create return %d\n",init_philos(&data));
    /* int m = 0;
    while (1)
    {
        printf("TIME %d is running...\n", get_time());
        m++;
    } */
    mutex_destroy(&data);
    printf("Number of philosophers: %d\n", philos.num_of_philosophers);
}

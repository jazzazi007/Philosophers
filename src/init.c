#include "../include/philosophers.h"

int init_mutex(t_data *data)
{
    if (pthread_mutex_init(&data->mutex, NULL) != 0)
    {
        printf("Error: Mutex initialization failed\n");
        return (1);
    }
    return (0);
}

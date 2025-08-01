#include "../include/philosophers.h"

time_t get_time_ms(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1)
    {
        write(2, "gettimeofday() error\n", 22);
        return -1;
    }
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
#include "philo.h"

long get_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}


#include "philo_one.h"

int philo_info_init(t_arg *arg, t_philo **philo)
{   
    int i;

    i = 0;
    if (!(*philo = (t_philo *)malloc(sizeof(t_philo) * arg->number_of_philosopher)))
    {
        printf("Malloc philo in philo_info_init failed, sorry\n");
        return (0);
    }
    if (!(arg->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * arg->number_of_philosopher)))
    {
        printf("Malloc fork in philo_info_init failed, sorry\n");
        return (0);
    }
    if (!(arg->pro = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * arg->number_of_philosopher)))
    {
        printf("Malloc fork in philo_info_init failed, sorry\n");
        return (0);
    }
    while (i < arg->number_of_philosopher)
    {
        (*philo)[i].arg = arg;
        (*philo)[i].philo_num = i;
        i++;
    }
    return (1);
}

int    start_time(t_arg *arg)
{
    struct timeval t1;

    gettimeofday(&t1, NULL);
    arg->start = (t1.tv_sec * 1000) + (t1.tv_usec / 1000);
    return (1);
}

int main(int ac, char **av)
{
    t_arg   arg;
    t_philo *philo;

    memset(&arg, 0, sizeof(t_arg));
    if (!args(ac, av, &arg))
        return (0);
    //printtest(&arg);
    if (!philo_info_init(&arg, &philo) || !start_time(&arg)
    || !create_mutex(&philo, arg.number_of_philosopher)
    || !create_thread(&philo, arg.number_of_philosopher))
    {
        destroy(&philo, arg.number_of_philosopher);
        return (0);
    }
    wait_threads(&philo, arg.number_of_philosopher);
    destroy(&philo, arg.number_of_philosopher);
    return (1);
}
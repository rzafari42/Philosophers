#include "philo_one.h"

void take_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->arg->fork[philo->philo_num]);
    if (philo->philo_num == 0)
        pthread_mutex_lock(&philo->arg->fork[philo->arg->number_of_philosopher - 1]);
    else
        pthread_mutex_lock(&philo->arg->fork[philo->philo_num - 1]);
    print(philo, Fork, get_time() - philo->arg->start);
}

void eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->arg->pro[philo->philo_num]);
    (philo->mealnum)++;
    print(philo, Eat, get_time() - philo->arg->start);
    philo->lastmeal = get_time();
    ft_wait(philo->arg->time_to_eat);
    pthread_mutex_unlock(&philo->arg->pro[philo->philo_num]);
}

void drop_fork(t_philo *philo)
{
    pthread_mutex_unlock(&philo->arg->fork[philo->philo_num]);
    if (philo->philo_num == 0)
        pthread_mutex_unlock(&philo->arg->fork[philo->arg->number_of_philosopher - 1]);
    else
        pthread_mutex_unlock(&philo->arg->fork[philo->philo_num - 1]);
}

void sleeping(t_philo *philo)
{
    print(philo, Sleep, get_time() - philo->arg->start);
    ft_wait(philo->arg->time_to_sleep);
}

int		meals_eaten(t_philo *philo)
{
	int stop;

    stop = 0;
    pthread_mutex_lock(&(philo->arg->check));
    if (philo->arg->number_of_time_each_philosophers_must_eat && 
    philo->mealnum == philo->arg->number_of_time_each_philosophers_must_eat)
        stop = 1;
    pthread_mutex_unlock(&(philo->arg->check));
    return (stop);
}

static void *philo_start(void *arguments)
{
    t_philo   *philo;
    struct timeval t2;
    long time;

    philo = (t_philo *)arguments;
    time = 0;
    while (philo->arg->died != 1 && !meals_eaten(philo))
    {    
        if ((time - philo->lastmeal) > (long)philo->arg->time_to_die)
            print(philo, Died, time - philo->arg->start);
        take_fork(philo);
        eating(philo);
        drop_fork(philo);
        sleeping(philo);
        print(philo, Think, get_time() - philo->arg->start);
        time = get_time();
    }
    return (NULL);
}

int create_mutex(t_philo **philo, int nb_philo)
{
    int i;

    i = 0;
    while (i < nb_philo)
    {
        if (pthread_mutex_init(&(*philo)[i].arg->fork[i], NULL) != 0)
        {
            printf("Mutex initalization failed\n");
            return (0);
        }
        if (pthread_mutex_init(&(*philo)[i].arg->pro[i], NULL) != 0)
        {
            printf("Mutex initalization failed\n");
            return (0);
        }
        i++;
    }
    if (pthread_mutex_init(&(*philo)->arg->status, NULL) != 0)
    {
        printf("Mutex initalization failed\n");
        return (0);
    }
    if (pthread_mutex_init(&(*philo)->arg->check, NULL) != 0)
    {
        printf("Mutex initalization failed\n");
        return (0);
    }
    return (1);
}

int create_thread(t_philo **philo, int nb_philo)
{
    int i;

    i = 0;
    while (i < nb_philo)
    {
        if (pthread_create(&((*philo)[i].threads), NULL, philo_start, &(*philo)[i]) != 0)
        {
            printf("Failed while creating threads\n");
            return (0);
        }
        i += 2;
    }
    ft_wait(1);
    i = 1;
    while (i < nb_philo)
    {
        if (pthread_create(&((*philo)[i].threads), NULL, philo_start, &(*philo)[i]) != 0)
        {
            printf("Failed while creating threads\n");
            return (0);
        }
        i += 2;
    }
    return (1);
}

void destroy(t_philo **philo, int nb_philo)
{
    int i;

    i = 0;
    while (i < nb_philo)
    {
        pthread_mutex_destroy(&((*philo)[i].arg->fork[i]));
        pthread_mutex_destroy(&((*philo)[i].arg->pro[i]));
        pthread_mutex_destroy(&((*philo)[i].arg->status));
        pthread_mutex_destroy(&((*philo)[i].arg->check));
        i++;
    }
    free ((*philo)->arg->fork);
    free ((*philo)->arg->pro);
    free (*philo);
}

int wait_threads(t_philo **philo, int nb_philo)
{
    int i;
    void** l;

    i = 0;
    while (i < nb_philo)
    {
        if (pthread_join((*philo)[i].threads, NULL) != 0)
        {
            printf("Issue with one of pthread_join\n");
            return (0);
        }
        i++;
    }
    return (1);
}

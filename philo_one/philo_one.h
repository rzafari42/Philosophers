#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_arg
{
    int     number_of_philosopher;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     number_of_time_each_philosophers_must_eat;
    int     died;
    long    start;
    pthread_mutex_t     *fork;
    pthread_mutex_t     *pro;
    pthread_mutex_t     status;
    pthread_mutex_t     check;
}               t_arg;

typedef struct  s_philo
{
    int                 philo_num;
    long                lastmeal;
    int                 mealnum;
    int                 condstop;
    pthread_t           threads;
    t_arg               *arg;
}               t_philo;

typedef enum    s_status
{
    Fork,
    Eat,
    Sleep,
    Think,
    Died
}               t_status;

int     args(int ac, char **av, t_arg *arg);
int     checking(int ac, char **av);
void    catch_arg(int ac, char **av, t_arg *arg);
int     check_arg(int ac, t_arg *arg);
int     create_mutex(t_philo **philo, int nb_philo);
int     create_thread(t_philo **philo, int nb_philo);
void    destroy(t_philo **philo, int nb_philo);
int     wait_threads(t_philo **philo, int nb_philo);
int     philo_info_init(t_arg *arg, t_philo **philo);
static void *philo_start(void *arguments);
int     start_time(t_arg *arg);
int		meals_eaten(t_philo *philo);
void    ft_wait(long timetowait);
long    get_time();

void    take_fork(t_philo *philo);
void    drop_fork(t_philo *philo);
void    eating(t_philo *philo);
void    sleeping(t_philo *philo);
void    thinking(t_philo *philo);
void		print(t_philo *philo, t_status status, long time);

void    printtest(t_arg *args);
int     ft_atoi(const char *str);
void	inc_stop(t_philo *params);

#endif

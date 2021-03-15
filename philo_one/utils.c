#include "philo_one.h"

void		print(t_philo *philo, t_status status, long time)
{
	pthread_mutex_lock(&(philo->arg->status));
	if (philo->arg->died == 1)
	{
		pthread_mutex_unlock(&(philo->arg->status));
		return ;
	}
	if (status == Fork)
		printf("%-2ld %6d has taken a fork\n", time, philo->philo_num + 1);
	if (status == Eat)
		printf("%-2ld %6d is eating\n", time, philo->philo_num + 1);
	if (status == Sleep)
    	printf("%-2ld %6d is sleeping\n", time, philo->philo_num + 1);
	if (status == Think)
    	printf("%-2ld %6d is thinking\n", time, philo->philo_num + 1);
	if (status == Died)
	{
    	printf("%-2ld %6d died\n", time, philo->philo_num + 1);
		philo->arg->died = 1;
	}
	pthread_mutex_unlock(&(philo->arg->status));
}

long    get_time()
{
    struct timeval t2;

    gettimeofday(&t2, NULL);
    return (t2.tv_sec * 1000 + t2.tv_usec / 1000);
}

void		ft_wait(long timetowait)
{
	long time;

	time = get_time();
	while (get_time() < time + timetowait)
	{
		usleep(500);
	}
}

void printtest(t_arg *args)
{
    printf("number_of_philosopher = %d\n", args->number_of_philosopher);
    printf("time_to_die = %d\n", args->time_to_die);
    printf("time_to_eat = %d\n", args->time_to_eat);
    printf("time_to_sleep = %d\n", args->time_to_sleep);
    printf("number_of_time_each_philosophers_must_eat = %d\n", args->number_of_time_each_philosophers_must_eat);
    //printf("died = %d\n", args->philo_info->died);
   /* printf("eat = %d\n", args->philo.eat);
    printf("sleep = %d\n", args->philo.sleep);
    printf("think = %d\n", args->philo.think);*/
}

int	ft_atoi(const char *str)
{
	int sign;
	int ans;

	ans = 0;
	sign = 1;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
				|| *str == '\v' || *str == '\f'))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		ans = ans * 10 + (*str - 48);
		str++;
	}
	return (ans * sign);
}
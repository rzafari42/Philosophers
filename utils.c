#include "philosophers.h"

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

void    struc_initilization(t_infos *args)
{
        args->number_of_philosopher = 0;
        args->time_to_die = 0;
        args->time_to_eat = 0;
        args->time_to_sleep = 0;
        args->number_of_time_each_philosophers_must_eat = 0;
}

void    print_struct(t_infos *args)
{
        printf("args->number_of_philosopher = %d\n", args->number_of_philosopher);
        printf("args->time_to_die = %d\n", args->time_to_die);
        printf("args->time_to_eat = %d\n", args->time_to_eat);
        printf("args->time_to_sleep = %d\n", args->time_to_sleep);
        printf("args->number_of_time_each_philosophers_must_eat = %d\n", args->number_of_time_each_philosophers_must_eat); 
}

size_t	ft_strlen(const char *s)
{
	unsigned int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int     ft_strerror(char *s)
{
        write(1, s, ft_strlen(s));
        return (0);
}
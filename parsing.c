#include "philosophers.h"

int check_arg(t_infos *args, int ac)
{
        if ((args->number_of_philosopher && args->time_to_die
        && args->time_to_eat && args->time_to_sleep)== 0)
        {
                printf("arg error\n");
                return (0);
        }
        if (ac == 6 && args->number_of_time_each_philosophers_must_eat == 0)
            return (0);
        return (1);
}

int parsing(int ac, char **av, t_infos *args)
{
        if (ac < 5 || ac > 6)
                return (0);
        else
        {
                args->number_of_philosopher = ft_atoi(av[1]);
                args->time_to_die = ft_atoi(av[2]);
                args->time_to_eat = ft_atoi(av[3]);
                args->time_to_sleep = ft_atoi(av[4]);
                if (ac == 6)
                        args->number_of_time_each_philosophers_must_eat = ft_atoi(av[5]);
                if (!check_arg(args, ac))
                        return (0);
                return (1);
        }
}
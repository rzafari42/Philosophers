#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# define NULL_ARG   "Error: None of the args should be equal to zero"

typedef struct  s_infos
{
    unsigned int number_of_philosopher;
    unsigned int time_to_die;
    unsigned int time_to_eat;
    unsigned int time_to_sleep;
    unsigned int number_of_time_each_philosophers_must_eat;
}               t_infos;

void    struc_initilization(t_infos *args);
int     parsing(int ac, char **av, t_infos *args);
int     check_arg(t_infos *args, int ac);
int     ft_atoi(const char *str);
int     ft_strerror(char *s);
size_t  ft_strlen(const char *s);


void    print_struct(t_infos *args);
#endif
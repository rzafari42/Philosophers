/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:05:49 by rzafari           #+#    #+#             */
/*   Updated: 2021/04/29 19:29:19 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct	s_arg
{
	int					nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_must_eat;
	int					died;
	int					condstop;
	long				start;
	pthread_mutex_t		*fork;
	pthread_mutex_t		*checkifok;
	pthread_mutex_t		printstatus;
	pthread_mutex_t		checkifstop;
}				t_arg;

typedef struct	s_philo
{
	int					philo_num;
	long				lastmeal;
	int					mealnum;
	pthread_t			threads;
	pthread_t			checkifdie;
	t_arg				*arg;
}				t_philo;

typedef enum	e_status
{
	Fork,
	Eat,
	Sleep,
	Think,
	Died,
}				t_status;

int				args(int ac, char **av, t_arg *arg);
int				checking(int ac);
int				check_arg(int ac, t_arg *arg);
int				create_mutex(t_arg *arg);
int				create_thread(t_philo **philo, int nb_philo);
int				create_thread_next(t_philo **philo, int nb_philo);
int				wait_threads(t_philo **philo, int nb_philo);
int				philo_info_init(t_arg *arg, t_philo **philo);
int				start_time(t_arg *arg);
int				meals_eaten(t_philo *philo);
int				ft_atoi(const char *str);

long			get_time(void);

void			ft_wait(long timetowait);
void			destroy(t_philo **philo, int nb_philo);
void			catch_arg(int ac, char **av, t_arg *arg);
void			take_fork(t_philo *philo);
void			drop_fork(t_philo *philo);
void			eating(t_philo *philo);
void			sleeping(t_philo *philo);
void			thinking(t_philo *philo);
void			print(t_philo *philo, t_status status);
void			*philo_start(void *philosopher);
void			*supervisord(void *philosopher);

#endif

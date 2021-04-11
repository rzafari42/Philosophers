/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:00:06 by rzafari           #+#    #+#             */
/*   Updated: 2021/04/11 20:42:56 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		meals_eaten(t_philo *philo)
{
	int stop;

	stop = 0;
	sem_wait(philo->arg->checkifstop);
	if (philo->arg->nb_must_eat &&
	philo->mealnum == philo->arg->nb_must_eat)
		stop = 1;
	sem_post(philo->arg->checkifstop);
	return (stop);
}

void	*supervisord(void *philosopher)
{
	t_philo	*philo;
	long	time;

	time = 0;
	philo = (t_philo *)philosopher;
	while (philo->arg->died != 1 && !meals_eaten(philo))
	{
		sem_wait(philo->arg->checkifok[philo->philo_num]);
		if (philo->lastmeal != 0)
		{
			if (get_time() - philo->lastmeal > (long)philo->arg->time_to_die)
			{
				print(philo, Died);
				exit(SIG_DIED);
			}
		}
		sem_post(philo->arg->checkifok[philo->philo_num]);
	}
	return (NULL);
}

void	*philo_start(void *arg)
{
	t_philo		*philo;
	pthread_t	th;

	philo = (t_philo *)arg;
	if (pthread_create(&th, NULL, supervisord, arg) != 0)
	{
		printf("Failed while creating supervisord thread\n");
		return (0);
	}
	pthread_detach(th);
	while (philo->arg->died != 1)
	{
		take_fork(philo);
		eating(philo);
		drop_fork(philo);
		if (philo->arg->nb_must_eat &&
		philo->mealnum == philo->arg->nb_must_eat)
			break ;
		sleeping(philo);
		print(philo, Think);
	}
	if (philo->arg->died)
		exit(SIG_DIED);
	exit(0);
}

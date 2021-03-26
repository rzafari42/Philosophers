/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:00:06 by rzafari           #+#    #+#             */
/*   Updated: 2021/03/25 20:00:45 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		meals_eaten(t_philo *philo)
{
	int stop;

	stop = 0;
	sem_wait(philo->arg->checkifstop);
	if (philo->arg->nb_must_eat && philo->mealnum == philo->arg->nb_must_eat)
		stop = 1;
	sem_post(philo->arg->checkifstop);
	return (stop);
}

void	*check_die_cond(void *philosopher)
{
	t_philo	*philo;
	long	time;

	time = 0;
	philo = (t_philo *)philosopher;
	while ((philo->arg->died) != 1 && !meals_eaten(philo))
	{
		sem_wait(philo->arg->pro[philo->philo_num]);
		if (philo->lastmeal != 0)
			time = get_time();
		if (time - philo->lastmeal > (long)philo->arg->time_to_die)
			print(philo, Died);
		sem_post(philo->arg->pro[philo->philo_num]);
		ft_wait(8);
	}
	return (NULL);
}

void	*philo_start(void *arg)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)arg;
	time = 0;
	while (philo->arg->died != 1 && !meals_eaten(philo))
	{
		take_fork(philo);
		eating(philo);
		drop_fork(philo);
		sleeping(philo);
		print(philo, Think);
	}
	return (NULL);
}

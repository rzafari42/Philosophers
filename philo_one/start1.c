/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:00:23 by rzafari           #+#    #+#             */
/*   Updated: 2021/03/18 17:00:23 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->fork[philo->philo_num]);
	if (philo->philo_num == 0)
		pthread_mutex_lock(&philo->arg->fork[philo->arg->nb_philos - 1]);
	else
		pthread_mutex_lock(&philo->arg->fork[philo->philo_num - 1]);
	print(philo, Fork);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->pro[philo->philo_num]);
	print(philo, Eat);
	philo->mealnum++;
	philo->lastmeal = get_time();
	ft_wait(philo->arg->time_to_eat);
	pthread_mutex_unlock(&philo->arg->pro[philo->philo_num]);
}

void	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->arg->fork[philo->philo_num]);
	if (philo->philo_num == 0)
		pthread_mutex_unlock(&philo->arg->fork[philo->arg->nb_philos - 1]);
	else
		pthread_mutex_unlock(&philo->arg->fork[philo->philo_num - 1]);
}

void	sleeping(t_philo *philo)
{
	print(philo, Sleep);
	ft_wait(philo->arg->time_to_sleep);
}

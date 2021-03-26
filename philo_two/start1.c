/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:00:23 by rzafari           #+#    #+#             */
/*   Updated: 2021/03/26 12:48:26 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	take_fork(t_philo *philo)
{
	sem_wait(&philo->arg->fork[philo->philo_num]);
	sem_wait(&philo->arg->fork[philo->philo_num]);
	print(philo, Fork);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->arg->pro[philo->philo_num]);
	print(philo, Eat);
	philo->mealnum++;
	philo->lastmeal = get_time();
	ft_wait(philo->arg->time_to_eat);
	sem_post(philo->arg->pro[philo->philo_num]);
}

void	drop_fork(t_philo *philo)
{
	sem_post(&philo->arg->fork[philo->philo_num]);
	sem_post(&philo->arg->fork[philo->philo_num]);
}

void	sleeping(t_philo *philo)
{
	print(philo, Sleep);
	ft_wait(philo->arg->time_to_sleep);
}

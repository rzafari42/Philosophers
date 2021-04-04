/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:00:23 by rzafari           #+#    #+#             */
/*   Updated: 2021/04/04 22:01:44 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	take_fork(t_philo *philo)
{
	sem_wait(philo->arg->fork);
	print(philo, Fork);
	sem_wait(philo->arg->fork);
	print(philo, Fork);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->arg->checkifok[philo->philo_num]);
	print(philo, Eat);
	philo->mealnum++;
	//philo->lastmeal = get_time();
	ft_wait(philo->arg->time_to_eat);
	sem_post(philo->arg->checkifok[philo->philo_num]);
}

void	drop_fork(t_philo *philo)
{
	sem_post(philo->arg->fork);
	sem_post(philo->arg->fork);
}

void	sleeping(t_philo *philo)
{
	print(philo, Sleep);
	ft_wait(philo->arg->time_to_sleep);
}

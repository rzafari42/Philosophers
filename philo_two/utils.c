/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:05:45 by rzafari           #+#    #+#             */
/*   Updated: 2021/03/30 16:51:51 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	print(t_philo *philo, t_status status)
{
	long time;

	sem_wait(philo->arg->printstatus);
	time = get_time() - philo->arg->start;
	if (philo->arg->died == 1)
	{
		sem_post(philo->arg->printstatus);
		return ;
	}
	if (status == Fork)
		printf("%-2ld %6d has taken a fork\n", time, philo->philo_num + 1);
	else if (status == Eat)
		printf("%-2ld %6d is eating\n", time, philo->philo_num + 1);
	else if (status == Sleep)
		printf("%-2ld %6d is sleeping\n", time, philo->philo_num + 1);
	else if (status == Think)
		printf("%-2ld %6d is thinking\n", time, philo->philo_num + 1);
	else if (status == Died)
	{
		printf("%-2ld %6d died\n", time, philo->philo_num + 1);
		philo->arg->died = 1;
	}
	sem_post(philo->arg->printstatus);
}

long	get_time(void)
{
	struct timeval t2;

	gettimeofday(&t2, NULL);
	return (t2.tv_sec * 1000 + t2.tv_usec / 1000);
}

void	ft_wait(long timetowait)
{
	long time;

	time = get_time();
	while (get_time() < time + timetowait)
		usleep(500);
}

int		ft_atoi(const char *str)
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

void	destroy(t_philo **philo, int nb_philo, int iffree)
{
	int		i;

	i = 0;
	(void)nb_philo;
	while (i < nb_philo)
	{
		sem_close((*philo)->arg->checkifok[i]);
		sem_unlink((*philo)->arg->checkifok_num[i]);
		if (iffree)
			free((*philo)->arg->checkifok_num[i]);
		i++;
	}
	sem_close((*philo)->arg->fork);
	sem_close((*philo)->arg->printstatus);
	sem_close((*philo)->arg->checkifstop);
	sem_unlink(SEM_PRO);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_CHECK);
	if (iffree)
	{
		free((*philo)->arg->checkifok_num);
		free((*philo)->arg->checkifok);
		free(*philo);
	}
}

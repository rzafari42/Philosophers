/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:05:36 by rzafari           #+#    #+#             */
/*   Updated: 2021/03/30 15:59:16 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		create_mutex(t_philo **philo, int nb_philo)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		if ((pthread_mutex_init(&(*philo)[i].arg->fork[i], NULL) != 0) &&
		(pthread_mutex_init(&(*philo)[i].arg->checkifok[i], NULL) != 0))
		{
			printf("Mutex initalization failed\n");
			return (0);
		}
		i++;
	}
	if ((pthread_mutex_init(&(*philo)->arg->printstatus, NULL) != 0) &&
	(pthread_mutex_init(&(*philo)->arg->checkifstop, NULL) != 0))
	{
		printf("Mutex initalization failed\n");
		return (0);
	}
	return (1);
}

int		create_thread(t_philo **philo, int nb_philo)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		if ((pthread_create(&((*philo)[i].threads), NULL,
		philo_start, &(*philo)[i]) != 0))
		{
			printf("Failed while creating threads\n");
			return (0);
		}
		if (pthread_create(&((*philo)[i].checkifdie), NULL,
		supervisord, &(*philo)[i]) != 0)
		{
			printf("Failed while creating threads\n");
			return (0);
		}
		i += 2;
	}
	ft_wait(5);
	if (!create_thread_next(philo, nb_philo))
		return (0);
	return (1);
}

int		create_thread_next(t_philo **philo, int nb_philo)
{
	int i;

	i = 1;
	while (i < nb_philo)
	{
		if (pthread_create(&((*philo)[i].threads), NULL,
		philo_start, &(*philo)[i]) != 0)
		{
			printf("Failed while creating threads\n");
			return (0);
		}
		if (pthread_create(&((*philo)[i].checkifdie), NULL,
		supervisord, &(*philo)[i]) != 0)
		{
			printf("Failed while creating threads\n");
			return (0);
		}
		i += 2;
	}
	return (1);
}

int		wait_threads(t_philo **philo, int nb_philo)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		if (pthread_join((*philo)[i].threads, NULL) != 0)
		{
			printf("Issue with one of pthread_join\n");
			return (0);
		}
		if (pthread_join((*philo)[i].checkifdie, NULL) != 0)
		{
			printf("Issue with one of pthread_join\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	destroy(t_philo **philo, int nb_philo)
{
	int i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&((*philo)[i].arg->fork[i]));
		pthread_mutex_destroy(&((*philo)[i].arg->checkifok[i]));
		pthread_mutex_destroy(&((*philo)[i].arg->printstatus));
		pthread_mutex_destroy(&((*philo)[i].arg->checkifstop));
		i++;
	}
	free((*philo)->arg->fork);
	free((*philo)->arg->checkifok);
	free(*philo);
}

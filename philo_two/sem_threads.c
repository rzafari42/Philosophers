/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:05:36 by rzafari           #+#    #+#             */
/*   Updated: 2021/04/08 14:59:09 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		create_pro_sem_id(t_philo **philo)
{
	int			i;
	int			l;
	char		*s;

	if (!((*philo)->arg->checkifok_num = malloc(sizeof(const char *) *
	(*philo)->arg->nb_philos)))
	{
		printf("Malloc in create_pro_sem_id failed, sorry\n");
		return (0);
	}
	i = 0;
	while (i < (*philo)->arg->nb_philos)
	{
		s = ft_strjoin(SEM_PRO_NAME, ft_inttochar(i));
		l = ft_strlen(s);
		if (!((*philo)->arg->checkifok_num[i] = (char*)malloc(sizeof(char *)
		* l)))
		{
			printf("Malloc in create_pro_sem_id failed, sorry\n");
			return (0);
		}
		ft_strcpy((*philo)->arg->checkifok_num[i++], s);
		free(s);
	}
	return (1);
}

int		create_sem(t_philo **philo, int nb_philo)
{
	int	i;

	i = 0;
	destroy(philo, nb_philo, 0);
	(*philo)->arg->fork = sem_open(SEM_FORKS, O_CREAT, 777,
	(*philo)->arg->nb_philos);
	(*philo)->arg->printstatus = sem_open(SEM_PRINT, O_CREAT, 777, 1);
	(*philo)->arg->checkifstop = sem_open(SEM_CHECK, O_CREAT, 777, 1);
	while (i < (*philo)->arg->nb_philos)
	{
		(*philo)->arg->checkifok[i] = sem_open((*philo)->arg->checkifok_num[i],
		O_CREAT, 777, 1);
		i++;
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
	ft_wait(4);
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

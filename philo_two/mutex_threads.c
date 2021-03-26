/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:05:36 by rzafari           #+#    #+#             */
/*   Updated: 2021/03/25 21:57:31 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	create_pro_sem_id(t_philo **philo)
{
	int			i;
	int			l;
	char		*s;

	if (!((*philo)->arg->protection_num = malloc(sizeof(const char *) * (*philo)->arg->nb_philos)))
	{
		printf("Malloc in create_pro_sem_id failed, sorry\n");
		return (0);
	}
	i = 0;
	while (i < (*philo)->arg->nb_philos)
	{
		s = ft_strjoin("philo_", ft_inttochar(i));
		l = ft_strlen(s);
		if (!((*philo)->arg->protection_num[i] = (char*)malloc(sizeof(char *) * l)))
		{
			printf("Malloc in create_pro_sem_id failed, sorry\n");
			return (0);
		}
		ft_strcpy((*philo)->arg->protection_num[i], s);
		free(s);
		i++;
	}
	return (1);
}

int		create_sem(t_philo **philo, int nb_philo)
{
	int	i;

	i = 0;
	destroy(philo, nb_philo, 0);
	(*philo)->arg->fork = sem_open("/fork", O_CREAT, 777, (*philo)->arg->nb_philos);
	(*philo)->arg->printstatus = sem_open("/print", O_CREAT, 777, 1);
	(*philo)->arg->checkifstop = sem_open("/check", O_CREAT, 777, 1);
	while (i < (*philo)->arg->nb_philos)
	{
		(*philo)->arg->pro[i] = sem_open((*philo)->arg->protection_num[i], O_CREAT, 777, 1);
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
		check_die_cond, &(*philo)[i]) != 0)
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
		check_die_cond, &(*philo)[i]) != 0)
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

void	destroy(t_philo **philo, int nb_philo, int iffree)
{
	int		i;

	i = 0;
	while (i < nb_philo)
	{
		sem_close((*philo)->arg->pro[i]);
		sem_unlink((*philo)->arg->protection_num[i]);
		if (iffree)
			free((*philo)->arg->protection_num[i]);
		i++;
	}
	
	sem_close((*philo)->arg->fork);
	sem_close((*philo)->arg->printstatus);
	sem_close((*philo)->arg->checkifstop);
	sem_unlink("/pro");
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/check");
	if (iffree)
	{
		free((*philo)->arg->protection_num);
		free((*philo)->arg->pro);
		free(*philo);
	}
}

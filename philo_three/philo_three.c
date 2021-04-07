/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:06:18 by rzafari           #+#    #+#             */
/*   Updated: 2021/04/07 14:52:41 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	philo_info_init(t_arg *arg, t_philo **philo)
{
	int i;

	i = 0;
	if (!(*philo = (t_philo *)malloc(sizeof(t_philo) * arg->nb_philos)) ||
	!(arg->checkifok = malloc(sizeof(sem_t *) * arg->nb_philos)))
	{
		printf("Malloc philo in philo_info_init failed, sorry\n");
		return (0);
	}
	while (i < arg->nb_philos)
	{
		(*philo)[i].arg = arg;
		(*philo)[i].philo_num = i;
		i++;
	}
	return (1);
}

int	start_time(t_arg *arg)
{
	struct timeval t1;

	gettimeofday(&t1, NULL);
	arg->start = (t1.tv_sec * 1000) + (t1.tv_usec / 1000);
	return (1);
}

int	main(int ac, char **av)
{
	t_arg	arg;
	t_philo *philo;

	memset(&arg, 0, sizeof(t_arg));
	if (!args(ac, av, &arg))
		return (0);
	if (!philo_info_init(&arg, &philo)
	|| !start_time(&arg)
	|| !create_pro_sem_id(&philo)
	|| !create_sem(&philo, arg.nb_philos))
	{
		destroy(&philo, arg.nb_philos, 1);
		return (0);
	}
	lets_fork(&philo);
	destroy(&philo, arg.nb_philos, 1);
	return (1);
}

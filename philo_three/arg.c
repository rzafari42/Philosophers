/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:05:41 by rzafari           #+#    #+#             */
/*   Updated: 2021/03/31 12:55:38 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		checking(int ac)
{
	if (ac < 5)
	{
		printf("Not enough arguments !\n");
		return (0);
	}
	else if (ac > 6)
	{
		printf("Too many arguments !\n");
		return (0);
	}
	return (1);
}

void	catch_arg(int ac, char **av, t_arg *arg)
{
	arg->nb_philos = ft_atoi((const char *)av[1]);
	arg->time_to_die = ft_atoi((const char *)av[2]);
	arg->time_to_eat = ft_atoi((const char *)av[3]);
	arg->time_to_sleep = ft_atoi((const char *)av[4]);
	if (ac == 6)
		arg->nb_must_eat = ft_atoi((const char *)av[5]);
}

int		check_arg(int ac, t_arg *arg)
{
	if (arg->nb_philos > 1 && arg->time_to_die > 0
	&& arg->time_to_eat > 0 && arg->time_to_sleep > 0)
	{
		if (ac == 6 && arg->nb_must_eat > 0)
			return (1);
		return (1);
	}
	if (arg->nb_philos < 2)
		printf("Not enough philosophers\n");
	if (arg->time_to_die < 1)
		printf("Time to die must be greater\n");
	if (arg->time_to_eat < 1)
		printf("Time to eat must be greater\n");
	if (arg->time_to_sleep < 1)
		printf("Time to sleep must be greater\n");
	if (ac == 6 && arg->nb_must_eat < 1)
		printf("Number of time each philosophers must eat must be greater\n");
	return (0);
}

int		args(int ac, char **av, t_arg *arg)
{
	if (!checking(ac))
		return (0);
	catch_arg(ac, av, arg);
	if (!check_arg(ac, arg))
		return (0);
	return (1);
}

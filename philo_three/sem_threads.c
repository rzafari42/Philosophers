/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:05:36 by rzafari           #+#    #+#             */
/*   Updated: 2021/04/09 19:56:18 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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

void	endproc(t_philo **philo)
{
	int	i;
	int	status;

	i = 0;
	while (i < (*philo)->arg->nb_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == SIG_DIED)
		{
			i = 0;
			while (i < (*philo)->arg->nb_philos)
			{
				if ((*philo)[i].proc)
					kill((*philo)[i].proc, SIGINT);
				i++;
			}
			break ;
		}
		i++;
	}
}

void	lets_fork(t_philo **philo)
{
	int		i;

	i = 0;
	while (i < (*philo)->arg->nb_philos)
	{
		(*philo)[i].proc = fork();
		if ((*philo)[i].proc == -1)
		{
			printf("forking issue\n");
			endproc(philo);
			return ;
		}
		else if ((*philo)[i].proc == 0)
			philo_start(&(*philo)[i]);
		i += 2;
	}
	ft_wait(4);
	lets_fork_next(philo);
}

void	lets_fork_next(t_philo **philo)
{
	int	i;

	i = 1;
	while (i < (*philo)->arg->nb_philos)
	{
		(*philo)[i].proc = fork();
		if ((*philo)[i].proc == -1)
		{
			printf("forking issue\n");
			endproc(philo);
			return ;
		}
		else if ((*philo)[i].proc == 0)
			philo_start(&(*philo)[i]);
		i += 2;
	}
	endproc(philo);
	return ;
}

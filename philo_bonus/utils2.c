/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 02:46:30 by aklaikel          #+#    #+#             */
/*   Updated: 2022/04/11 03:19:59 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bonus.h"

t_philo_b	*philos_create(t_args_b *data)
{
	t_philo_b	*philos;
	int			i;

	philos = malloc(sizeof(t_philo_b) * data->nbr_of_philos);
	i = -1;
	while (++i < data->nbr_of_philos)
	{
		philos[i].index = i + 1;
		philos[i].last_eat = get_time();
		philos[i].args = data;
	}
	return (philos);
}

void	semaphore_start(t_philo_b *philos)
{
	sem_unlink("/pen");
	sem_unlink("/fork");
	philos[0].args->pen = sem_open("/pen", O_CREAT | O_EXCL, 0644, 1);
	if (philos[0].args->pen == SEM_FAILED)
		printf("Can't create the sem pen !\n");
	philos[0].args->forks = sem_open("/fork", \
		O_CREAT | O_EXCL, 0644, philos[0].args->nbr_of_philos);
	if (philos[0].args->forks == SEM_FAILED)
		printf("Can't create the sem forks !\n");
}

void	killpids_sem(t_philo_b *philos)
{
	int	i;
	int	status;
	int	j;

	i = -1;
	while (++i < philos->args->nbr_of_philos)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			j = 0;
			while (j < philos->args->nbr_of_philos)
			{
				kill(philos->args->pids[j], SIGTERM);
				j++;
			}
		}
	}
	sem_close(philos->args->forks);
	sem_close(philos->args->pen);
}

void	check_death(t_philo_b *philo)
{
	while (1)
	{
		if (philo->args->nbr_of_meals == 0)
			exit(0);
		if ((int)(get_time() - philo->last_eat) > philo->args->time_to_die)
		{
			sem_wait(philo->args->pen);
			printf("%ld %d die\n", \
				(get_time() - philo->args->time_start), philo->index);
			exit(1);
		}
		usleep(50);
	}
}

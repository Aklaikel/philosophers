/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 02:24:49 by aklaikel          #+#    #+#             */
/*   Updated: 2022/04/13 02:09:16 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cont_routine(t_philo_b *philo)
{
	printf("%ld %d is eating\n", \
		(get_time() - philo->args->time_start), philo->index);
	sem_post(philo->args->pen);
	ft_usleep(philo->args->time_to_eat);
	philo->last_eat = get_time();
	philo->args->nbr_of_meals--;
	if (philo->args->nbr_of_meals == 0)
		exit(0);
	sem_wait(philo->args->pen);
	printf("%ld %d is sleeping\n", \
		(get_time() - philo->args->time_start), philo->index);
	sem_post(philo->args->pen);
	ft_usleep(philo->args->time_to_sleep);
	sem_wait(philo->args->pen);
	printf("%ld %d is thinking\n", \
		(get_time() - philo->args->time_start), philo->index);
	sem_post(philo->args->pen);
}

void	*routine(t_philo_b *philo)
{
	if (philo->index & 1)
		ft_usleep(philo->args->time_to_eat);
	while (philo->args->nbr_of_meals)
	{
		sem_wait(philo->args->forks);
		sem_wait(philo->args->pen);
		printf("%ld %d has taken a fork\n", \
			(get_time() - philo->args->time_start), philo->index);
		sem_post(philo->args->pen);
		sem_post(philo->args->forks);
		sem_wait(philo->args->forks);
		sem_wait(philo->args->pen);
		printf("%ld %d has taken a fork\n", \
			(get_time() - philo->args->time_start), philo->index);
		sem_post(philo->args->pen);
		sem_post(philo->args->forks);
		sem_wait(philo->args->pen);
		cont_routine(philo);
	}
	return (philo);
}

void	child_process(t_philo_b *philo)
{
	pthread_t	th;

	pthread_create(&th, NULL, (void *)(void *)&routine, philo);
	check_death(philo);
	exit(1);
}

void	start_philos(t_philo_b *philos)
{
	int	i;

	semaphore_start(philos);
	i = -1;
	while (++i < philos->args->nbr_of_philos)
	{
		philos->args->pids[i] = fork();
		if (philos->args->pids[i] == 0)
			child_process(&philos[i]);
	}
	killpids_sem(philos);
}

int	main(int ac, char **av)
{
	t_args_b	*data;
	t_philo_b	*philos;

	if (ac != 5 && ac != 6)
		return (printf("args error\n"), 0);
	if (!philo_pars(av, ac))
		return (printf("error\n"), 2);
	data = parse_data(av);
	if (!data)
		return (free(data), printf("table was not created\n"), 2);
	philos = philos_create(data);
	if (!philos)
		return (printf("philos was not created\n"), 2);
	start_philos(philos);
	free(data);
	free(philos);
}

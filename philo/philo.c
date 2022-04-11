/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:16:55 by aklaikel          #+#    #+#             */
/*   Updated: 2022/04/11 03:53:50 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cont_routine(t_philo	*philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->next_fork);
	pthread_mutex_lock(&philo->args->pen);
	printf("%ld %d is sleeping\n", \
		(get_time() - philo->args->time_start), philo->index);
	pthread_mutex_unlock(&philo->args->pen);
	ft_usleep(philo->args->time_to_sleep);
	pthread_mutex_lock(&philo->args->pen);
	printf("%ld %d is thinking\n", \
		(get_time() - philo->args->time_start), philo->index);
	pthread_mutex_unlock(&philo->args->pen);
}

void	*routine(t_philo *philo)
{
	if (philo->index & 1)
		ft_usleep(philo->args->time_to_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->args->pen);
		printf("%ld %d has taken a fork\n", \
			(get_time() - philo->args->time_start), philo->index);
		pthread_mutex_unlock(&philo->args->pen);
		pthread_mutex_lock(philo->next_fork);
		pthread_mutex_lock(&philo->args->pen);
		printf("%ld %d has taken a fork\n", \
			(get_time() - philo->args->time_start), philo->index);
		printf("%ld %d is eating\n", \
			(get_time() - philo->args->time_start), philo->index);
		pthread_mutex_unlock(&philo->args->pen);
		ft_usleep(philo->args->time_to_eat);
		philo->last_eat = get_time();
		philo->nbr_of_meals++;
		cont_routine(philo);
	}
	return (NULL);
}

void	start_philos(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos[0].args->nbr_of_philos)
	{
		philos[i].next_fork
			= &philos[(i + 1) % philos[i].args->nbr_of_philos].fork;
		philos[i].last_eat = get_time();
		philos[i].nbr_of_meals = 0;
		philos[i].counted = false;
	}
	i = -1;
	while (++i < philos[0].args->nbr_of_philos)
	{
		pthread_create(&philos[i].th, NULL,
			(void *)(void *)routine, &(philos[i]));
	}
}

int	main(int ac, char **av)
{
	t_args	*data;
	t_philo	*philos;

	if (ac != 5 && ac != 6)
		return (printf("args error\n"), 0);
	if (!philo_pars(av, ac))
		return (printf("error\n"), 0);
	data = init_philo(av);
	if (!data)
		return (printf("table was not created\n"), 2);
	philos = create_philos(data);
	if (!philos)
		return (free(data), printf("An error has been occured\n"), 2);
	start_philos(philos);
	check_finish(philos);
}

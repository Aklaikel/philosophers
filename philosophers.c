/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:16:55 by aklaikel          #+#    #+#             */
/*   Updated: 2022/03/17 01:50:11 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = get_time();
	while (get_time() < start + time)
		usleep(50);
}

unsigned long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

t_args	*init_philo(char **args)
{
	t_args	*data;

	data = malloc(sizeof(t_args));
	if (!data)
		return (NULL);
	data->nbr_of_philos = ft_atoi(args[1]);
	data->time_to_die = ft_atoi(args[2]);
	data->time_to_eat = ft_atoi(args[3]);
	data->time_to_sleep = ft_atoi(args[4]);
	data->nbr_of_meals = ft_atoi(args[5]);
	if (pthread_mutex_init(&data->pen, NULL) == -1)
		return (free(data), NULL);
	data->time_start = get_time();
	return (data);
}

t_philo	*create_philos(t_args	*data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->nbr_of_philos)
	{
		philos[i].index = i;
		philos[i].last_eat = get_time();
		if (pthread_mutex_init(&philos[i].fork, NULL) == -1)
			return (free(philos), NULL);
		philos[i].args = data;
		i++;
	}
	return (philos);
}

void	*routine(t_philo *philo)
{
	if (philo->index & 1)
		ft_usleep(philo->args->time_to_eat / 2);
	while (1) 
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->args->pen);
		printf("%ld %d has taken a fork\n", (get_time() - philo->args->time_start), philo->index);
		pthread_mutex_unlock(&philo->args->pen);
		pthread_mutex_lock(philo->next_fork);
		pthread_mutex_lock(&philo->args->pen);
		printf("%ld %d has taken a fork\n", (get_time() - philo->args->time_start), philo->index);
		printf("%ld %d is eating\n", (get_time() - philo->args->time_start), philo->index);
		pthread_mutex_unlock(&philo->args->pen);
		ft_usleep(philo->args->time_to_eat);
		philo->last_eat = get_time();
		philo->nbr_of_meals++;
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->next_fork);
		pthread_mutex_lock(&philo->args->pen);
		printf("%ld %d is sleeping\n", (get_time() - philo->args->time_start), philo->index);
		pthread_mutex_unlock(&philo->args->pen);
		ft_usleep(philo->args->time_to_sleep);
		pthread_mutex_lock(&philo->args->pen);
		printf("%ld %d is thinking\n", (get_time() - philo->args->time_start), philo->index);
		pthread_mutex_unlock(&philo->args->pen);
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
	}
	i = -1;
	while (++i < philos[0].args->nbr_of_philos)
	{
		pthread_create(&philos[i].th, NULL,
			(void *)(void *)routine, &(philos[i]));
	}
}

void	check_death(t_philo *philo)
{
	t_philo *tmp;
	int		i;

	int N = philo[0].args->nbr_of_philos;
	tmp = philo;
	ft_usleep(philo->args->time_to_die / 2);
	while(1)
	{
		i = -1;
		while (++i < N)
		{
			if ((int)(get_time() - philo[i].last_eat) > philo[i].args->time_to_die)
			{
				pthread_mutex_lock(&philo[i].args->pen);
				printf("%ld %d die\n", (get_time() - philo->args->time_start) , philo->index);
				return ;
			}
		}
		usleep(50);
	}
}

int	main(int ac, char **av)
{
	t_args	*data;
	t_philo	*philos;
	// int		i;

	if (ac != 5 && ac != 6)
		return (printf("args error\n"), 0);
	if (!philo_pars(av, ac))
		printf("error\n");
	data = init_philo(av);
	if (!data)
		return (printf("table was not created\n"), 2);
	philos = create_philos(data);
	if (!philos)
		return (free(data), printf("An error has been occured\n"), 2);
	start_philos(philos);
	check_death(philos);
	// check death (and complet number of meals)
// 	i = -1;
// 	while (++i)
// 	{
		
// 	}
// }
}

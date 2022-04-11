/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 03:26:44 by aklaikel          #+#    #+#             */
/*   Updated: 2022/04/11 03:27:00 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

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
		philos[i].index = i + 1;
		philos[i].last_eat = get_time();
		if (pthread_mutex_init(&philos[i].fork, NULL) == -1)
			return (free(philos), NULL);
		philos[i].args = data;
		i++;
	}
	return (philos);
}

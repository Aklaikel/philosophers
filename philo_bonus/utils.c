/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 02:42:44 by aklaikel          #+#    #+#             */
/*   Updated: 2022/04/11 03:18:22 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bonus.h"

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

t_args_b	*parse_data(char **av)
{
	t_args_b	*data;

	data = malloc(sizeof(t_args_b));
	if (!data)
		return (NULL);
	data->nbr_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->nbr_of_meals = ft_atoi(av[5]);
	data->time_start = get_time();
	return (data);
}

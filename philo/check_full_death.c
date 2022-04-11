/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_full_death.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 03:51:44 by aklaikel          #+#    #+#             */
/*   Updated: 2022/04/11 03:55:37 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

static void	counting(t_philo	*philo, int *count, int i)
{
	if (!philo[i].counted
		&& philo[i].nbr_of_meals >= philo[i].args->nbr_of_meals)
	{
		(*count)++;
		philo[i].counted = true;
	}
}

static void	kill_philo(t_philo	*philo)
{
	pthread_mutex_lock(&philo[0].args->pen);
	printf("%ld %d die\n", \
		(get_time() - philo->args->time_start), philo->index);
}

void	check_finish(t_philo *philo)
{
	int		i;
	int		count;

	count = 0;
	while (1)
	{
		i = -1;
		while (++i < philo[0].args->nbr_of_philos)
		{
			if ((int)(get_time() - philo[i].last_eat) \
				> philo[i].args->time_to_die)
			{
				kill_philo(philo);
				return ;
			}
			counting(philo, &count, i);
			if (count == philo[0].args->nbr_of_philos \
				&& philo[i].args->nbr_of_meals != -1)
			{
				pthread_mutex_lock(&philo[i].args->pen);
				return ;
			}
		}
	}
}

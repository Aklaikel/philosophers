/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:46:31 by aklaikel          #+#    #+#             */
/*   Updated: 2022/03/15 15:47:02 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	philo_pars(char **arg, int ac)
{
	int	i;

	i = 0;
	while (ac < ++i)
		if (ft_atoi(arg[i]) < 1)
			return (0);
	return (1);
}

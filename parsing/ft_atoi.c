/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:18:13 by aklaikel          #+#    #+#             */
/*   Updated: 2022/03/11 23:47:35 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str)
{
	int	i;
	int	s;
	int	ret;

	i = 0;
	s = 1;
	ret = 0;
	if (!str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < 48 && str[i] > 57)
			return (-1);
		ret *= 10 + (str[i] - 48);
		i++;
	}
	return (ret * s);
}

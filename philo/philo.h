/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:22:06 by aklaikel          #+#    #+#             */
/*   Updated: 2022/04/11 03:52:19 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_args
{
	int				time_to_sleep;
	int				time_to_think;
	int				time_to_eat;
	int				time_to_die;
	int				nbr_of_philos;
	int				nbr_of_meals;
	pthread_mutex_t	pen;
	long			time_start;
}				t_args;

typedef struct s_philo
{
	pthread_t		th;
	int				index;
	unsigned long	last_eat;
	t_args			*args;
	pthread_mutex_t	fork;
	int				nbr_of_meals;
	bool			counted;
	pthread_mutex_t	*next_fork;
	struct s_philo	*next;
}				t_philo;

int				ft_atoi(char *str);
int				philo_pars(char **arg, int ac);
unsigned long	get_time(void);
void			ft_usleep(unsigned long time);
t_args			*init_philo(char **args);
t_philo			*create_philos(t_args	*data);
void			*routine(t_philo *philo);
void			start_philos(t_philo *philos);
void			check_finish(t_philo *philo);
#endif
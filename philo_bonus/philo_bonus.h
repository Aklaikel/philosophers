/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:22:06 by aklaikel          #+#    #+#             */
/*   Updated: 2022/04/11 03:12:08 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>

typedef struct s_args_b
{
	int				time_to_sleep;
	int				time_to_think;
	int				time_to_eat;
	int				time_to_die;
	int				nbr_of_philos;
	int				nbr_of_meals;
	sem_t			*pen;
	sem_t			*forks;
	pid_t			pids[200];
	long			time_start;
}				t_args_b;
typedef struct s_philo_b
{
	pthread_t		th;
	int				index;
	unsigned long	last_eat;
	t_args_b		*args;
	int				nbr_of_meals;
	struct s_philo	*next;
}				t_philo_b;
int				ft_atoi(char *str);
int				philo_pars(char **arg, int ac);
unsigned long	get_time(void);
t_philo_b		*philos_create(t_args_b *data);
t_args_b		*parse_data(char **av);
void			ft_usleep(unsigned long time);
unsigned long	get_time(void);
void			semaphore_start(t_philo_b *philos);
void			killpids_sem(t_philo_b	*philos);
void			check_death(t_philo_b *philo);

#endif
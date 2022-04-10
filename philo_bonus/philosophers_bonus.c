/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklaikel <aklaikel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 02:24:49 by aklaikel          #+#    #+#             */
/*   Updated: 2022/04/10 07:42:40 by aklaikel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void ft_usleep(unsigned long time)
{
	unsigned long start;

	start = get_time();
	while (get_time() < start + time)
		usleep(50);
}

unsigned long get_time(void)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void killall_pids(int pids, int len)
{
	int i;

	i = -1;
	while (++i < len)
		kill(pids, SIGKILL);
}

t_args_b *parse_data(char **av)
{
	t_args_b *data;

	data = malloc(sizeof(t_args_b));
	if (!data)
		return (NULL);
	data->nbr_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->nbr_of_meals = ft_atoi(av[5]);
	data->time_start = get_time();
	printf("%d %d %d %d %d %ld\n", data->nbr_of_philos, data->time_to_die, data->time_to_eat,
		   data->time_to_sleep, data->nbr_of_meals, data->time_start);
	return (data);
}

t_philo_b *philos_create(t_args_b *data)
{
	t_philo_b *philos;
	int i;

	philos = malloc(sizeof(t_philo_b) * data->nbr_of_philos);
	i = -1;
	while (++i < data->nbr_of_philos)
	{
		philos[i].index = i + 1;
		philos[i].last_eat = get_time();
		philos[i].args = data;
	}
	return (philos);
}

void semaphore_start(t_philo_b *philos)
{
	sem_unlink("/pen");
	sem_unlink("/fork");
	philos[0].args->pen = sem_open("/pen", O_CREAT | O_EXCL, 0644, 1);
	if (philos[0].args->pen == SEM_FAILED)
		printf("Can't create the sem pen !\n");
	philos[0].args->forks = sem_open("/fork", O_CREAT | O_EXCL, 0644, philos[0].args->nbr_of_philos);
	if (philos[0].args->forks == SEM_FAILED)
		printf("Can't create the sem forks !\n");
}

void *routine(void *arg)
{
	t_philo_b *philo = arg;

	if (philo->index & 1)
	{
		printf("%d -> Before waiting ...\n", philo->index);	
		ft_usleep(philo->args->time_to_eat);
		printf("%d -> After waiting ...\n", philo->index);
	}
	while (philo->args->nbr_of_meals)
	{
		sem_wait(philo->args->forks);
		sem_wait(philo->args->pen);
		printf("%ld %d has taken a fork\n", (get_time() - philo->args->time_start), philo->index);
		sem_post(philo->args->pen);
		sem_post(philo->args->forks);
		
		sem_wait(philo->args->forks);
		sem_wait(philo->args->pen);
		printf("%ld %d has taken a fork\n", (get_time() - philo->args->time_start), philo->index);
		sem_post(philo->args->pen);
		sem_post(philo->args->forks);
		
		sem_wait(philo->args->pen);
		printf("%ld %d is eating\n", (get_time() - philo->args->time_start), philo->index);
		sem_post(philo->args->pen);
		
		ft_usleep(philo->args->time_to_eat);
		philo->last_eat = get_time();
		philo->args->nbr_of_meals--;
		if (philo->nbr_of_meals == 0)
			exit(0);
			
		sem_wait(philo->args->pen);
		printf("%ld %d is sleeping\n", (get_time() - philo->args->time_start), philo->index);
		sem_post(philo->args->pen);
		
		ft_usleep(philo->args->time_to_sleep);
		
		sem_wait(philo->args->pen);
		printf("%ld %d is thinking\n", (get_time() - philo->args->time_start), philo->index);
		sem_post(philo->args->pen);
	}
	return (arg);
}

void check_death(t_philo_b *philo)
{
	while (1)
	{
		if (philo->args->nbr_of_meals == 0)
			exit(0);
		if ((int)(get_time() - philo->last_eat) > philo->args->time_to_die)
		{
			sem_wait(philo->args->pen);
			printf("%ld %d die\n", (get_time() - philo->args->time_start), philo->index);
			exit(1);
		}
		usleep(50);
	}
}

void child_process(t_philo_b *philo)
{
	pthread_t th;
	pthread_create(&th, NULL, &routine, philo);
	check_death(philo);
	exit(1);
}

void start_philos(t_philo_b *philos)
{
	int i;
	int status;

	semaphore_start(philos);
	i = -1;
	while (++i < philos->args->nbr_of_philos)
	{
		philos->args->pids[i] = fork(); // TODO: protect the fork
		if (philos->args->pids[i] == 0)
			child_process(&philos[i]);
	}
	i = -1;
	while (++i < philos->args->nbr_of_philos)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			int j = 0;
			while (j < philos->args->nbr_of_philos)
			{
				kill(philos->args->pids[j], SIGTERM);
				j++;
			}
		}
	}
	sem_close(philos->args->forks);
	sem_close(philos->args->pen);
}

int main(int ac, char **av)
{
	t_args_b *data;
	t_philo_b *philos;

	if (ac != 5 && ac != 6)
		return (printf("args error\n"), 0);
	if (!philo_pars(av, ac))
		printf("error\n");
	data = parse_data(av);
	if (!data)
		return (printf("table was not created\n"), 2);
	philos = philos_create(data);
	start_philos(philos);
}

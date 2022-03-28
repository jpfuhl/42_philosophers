/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfuhl <jpfuhl@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:57:25 by jpfuhl            #+#    #+#             */
/*   Updated: 2022/03/28 19:19:24 by jpfuhl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	drop_all_forks(t_philo *philo)
{
	int		count;
	t_philo	*current;

	count = 0;
	current = philo;
	while (count < philo->data->number_of_philos)
	{
		pthread_mutex_unlock(&current->fork);
		current = current->next;
		count += 1;
	}
}

void	kill_philo(t_philo *philo)
{
	long	time;

	time = get_current_time(philo);
	if (time > philo->last_meal + philo->data->time.dying)
	{
		pthread_mutex_lock(&philo->data->print);
		if (!philo->data->someone_died)
		{
			printf("%8ld %d died\n", time, philo->id);
			philo->data->someone_died = TRUE;
		}
		drop_all_forks(philo);
		pthread_mutex_unlock(&philo->data->print);
	}
}

bool	check_death(t_philo *philo)
{
	bool	value;

	pthread_mutex_lock(&philo->data->death);
	value = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->death);
	return (value);
}

void	*watch_philo_threads(void *arg)
{
	t_philo	*current;

	current = arg;
	pthread_mutex_lock(&current->data->start);
	pthread_mutex_unlock(&current->data->start);
	usleep(current->data->time.eating / 2);
	while (!check_death(current) && current->state != FINISHED)
	{
		kill_philo(current);
		current = current->next;
	}
	return (NULL);
}

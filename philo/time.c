/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfuhl <jpfuhl@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 20:12:26 by jpfuhl            #+#    #+#             */
/*   Updated: 2022/03/28 19:20:12 by jpfuhl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(t_philo *philo, long limit)
{
	long	current_time;
	long	breaking_point;

	current_time = get_current_time(philo);
	breaking_point = current_time + limit;
	while (current_time < breaking_point)
	{
		if (philo->data->number_of_philos > 30)
			usleep (philo->data->number_of_philos);
		else
			usleep (10);
		current_time = get_current_time(philo);
	}
}

long	get_limit(t_philo *philo)
{
	long	limit;

	limit = 0;
	if (philo->state == FINISHED)
		limit = -1;
	else if (philo->state == EATING)
		limit = philo->data->time.eating;
	else if (philo->state == SLEEPING)
		limit = philo->data->time.sleeping;
	return (limit);
}

long	get_current_time(t_philo *philo)
{
	struct timeval	time_of_day;
	long			current_time;

	gettimeofday(&time_of_day, NULL);
	current_time = (time_of_day.tv_sec * 1000) + (time_of_day.tv_usec / 1000);
	return (current_time - philo->data->time.start_time);
}

long	get_start_time(void)
{
	struct timeval	time_of_day;
	long			start_time;

	gettimeofday(&time_of_day, NULL);
	start_time = (time_of_day.tv_sec * 1000) + (time_of_day.tv_usec / 1000);
	return (start_time);
}

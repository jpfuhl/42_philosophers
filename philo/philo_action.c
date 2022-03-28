/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfuhl <jpfuhl@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:57:50 by jpfuhl            #+#    #+#             */
/*   Updated: 2022/03/28 19:07:25 by jpfuhl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_thinking(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->print);
	time = get_current_time(philo);
	if (!philo->data->someone_died)
		printf("%8ld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	philo->state = THINKING;
}

void	start_sleeping(t_philo *philo)
{
	long	time;

	philo->times_eaten += 1;
	drop_forks(philo);
	pthread_mutex_lock(&philo->data->print);
	time = get_current_time(philo);
	if (!philo->data->someone_died)
		printf("%8ld %d is sleeping\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	philo->state = SLEEPING;
}

void	start_eating(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->print);
	time = get_current_time(philo);
	philo->last_meal = time;
	if (!philo->data->someone_died)
		printf("%8ld %d is eating\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	philo->state = EATING;
}

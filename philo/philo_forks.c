/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfuhl <jpfuhl@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:06:11 by jpfuhl            #+#    #+#             */
/*   Updated: 2022/03/28 19:19:43 by jpfuhl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	philo->fork_available = TRUE;
	pthread_mutex_unlock(&philo->next->fork);
	philo->next->fork_available = TRUE;
}

void	take_next_fork(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->next->fork);
	pthread_mutex_lock(&philo->data->print);
	time = get_current_time(philo);
	if (!philo->data->someone_died)
		printf("%8ld %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	if (philo->state == HAS_ONE_FORK)
		philo->state = HAS_TWO_FORKS;
	else
		philo->state = HAS_ONE_FORK;
	philo->next->fork_available = FALSE;
}

void	take_own_fork(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->data->print);
	time = get_current_time(philo);
	if (!philo->data->someone_died)
		printf("%8ld %d has taken a fork\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
	if (philo->state == HAS_ONE_FORK)
		philo->state = HAS_TWO_FORKS;
	else
		philo->state = HAS_ONE_FORK;
	philo->fork_available = FALSE;
}

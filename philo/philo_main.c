/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfuhl <jpfuhl@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:43:34 by jpfuhl            #+#    #+#             */
/*   Updated: 2022/03/28 19:44:45 by jpfuhl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_decision(t_philo *philo)
{
	if (philo->times_eaten == philo->data->number_of_meals)
		philo->state = FINISHED;
	else if (philo->state == THINKING || philo->state == DEFAULT)
	{
		if (philo->id % 2 == 1)
			take_own_fork(philo);
		else
			take_next_fork(philo);
	}
	else if (philo->state == HAS_ONE_FORK)
	{
		if (philo->data->number_of_philos <= 1)
			return ;
		if (philo->id % 2 == 1)
			take_next_fork(philo);
		else
			take_own_fork(philo);
	}
	else if (philo->state == HAS_TWO_FORKS)
		start_eating(philo);
	else if (philo->state == EATING)
		start_sleeping(philo);
	else if (philo->state == SLEEPING)
		start_thinking(philo);
}

void	philo_main(t_philo *philo)
{
	long	limit;
	long	current_time;

	while (!check_death(philo) && philo->state != FINISHED)
	{
		current_time = get_current_time(philo);
		philo_decision(philo);
		limit = get_limit(philo);
		if (limit == -1)
			break ;
		ft_sleep(philo, limit);
	}
}

void	*philo_launch(void *arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_mutex_lock(&philo->data->start);
	pthread_mutex_unlock(&philo->data->start);
	if (philo->id % 2 == 0)
		usleep(philo->data->time.eating / 2);
	if (philo->data->time.start_set == FALSE)
	{
		philo->data->time.start_set = TRUE;
		philo->data->time.start_time = get_start_time();
	}
	philo->last_meal = 0;
	philo_main(philo);
	return (NULL);
}

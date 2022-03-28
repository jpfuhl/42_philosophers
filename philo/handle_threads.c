/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfuhl <jpfuhl@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:52:36 by jpfuhl            #+#    #+#             */
/*   Updated: 2022/03/28 19:16:54 by jpfuhl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	join_philo_threads(t_data *data, t_philo *head)
{
	t_philo	*current;
	int		i;

	i = 0;
	current = head;
	while (i < data->number_of_philos)
	{
		pthread_join(current->thread, NULL);
		current = current->next;
		i++;
	}
}

void	create_philo_threads(t_data *data, t_philo *head)
{
	t_philo	*current;
	int		i;

	pthread_mutex_lock(&data->start);
	i = 0;
	current = head;
	while (i < data->number_of_philos)
	{
		pthread_create(&current->thread, NULL, &philo_launch, current);
		current = current->next;
		i++;
	}
	pthread_mutex_unlock(&data->start);
}

void	handle_threads(t_data *data, t_philo *head)
{
	pthread_t	reaper;

	pthread_create(&reaper, NULL, &watch_philo_threads, head);
	create_philo_threads(data, head);
	pthread_join(reaper, NULL);
	join_philo_threads(data, head);
}

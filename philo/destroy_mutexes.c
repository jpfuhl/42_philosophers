/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfuhl <jpfuhl@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:24:00 by jpfuhl            #+#    #+#             */
/*   Updated: 2022/03/28 19:18:28 by jpfuhl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutexes(t_data *data, t_philo *head)
{
	t_philo	*current;
	int		i;

	i = 0;
	current = head;
	while (i < data->number_of_meals)
	{
		pthread_mutex_destroy(&current->fork);
		current = current->next;
		if (!current)
			break ;
		i++;
	}
	pthread_mutex_destroy(&current->data->start);
	pthread_mutex_destroy(&current->data->print);
	pthread_mutex_destroy(&current->data->death);
}

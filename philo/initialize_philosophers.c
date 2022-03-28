/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philosophers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfuhl <jpfuhl@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 19:04:26 by jpfuhl            #+#    #+#             */
/*   Updated: 2022/03/28 19:18:58 by jpfuhl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fill_with_data(t_philo *philosopher, t_data *data, int pos)
{
	philosopher->i = pos;
	philosopher->id = pos + 1;
	philosopher->times_eaten = 0;
	philosopher->last_meal = 0;
	philosopher->state = DEFAULT;
	pthread_mutex_init(&philosopher->fork, NULL);
	philosopher->fork_available = TRUE;
	philosopher->data = data;
}

int	create_philo_list(t_philo *philosopher_head, t_data *data)
{
	t_philo	*philosopher_element;
	t_philo	*current;
	int		i;

	i = 1;
	current = philosopher_head;
	if (i == data->number_of_philos)
		current->next = philosopher_head;
	while (i < data->number_of_philos)
	{
		philosopher_element = malloc(sizeof(t_philo));
		if (!philosopher_element)
		{
			current->next = NULL;
			return (-1);
		}
		current->next = philosopher_element;
		current = philosopher_element;
		fill_with_data(philosopher_element, data, i);
		i++;
		if (i == data->number_of_philos)
			current->next = philosopher_head;
	}
	return (0);
}

t_philo	*initialize_philosophers(t_data *data)
{
	t_philo	*philosopher_head;
	int		check;

	philosopher_head = malloc(sizeof(t_philo));
	if (!philosopher_head)
		return (NULL);
	fill_with_data(philosopher_head, data, 0);
	check = create_philo_list(philosopher_head, data);
	if (check == -1)
	{
		destroy_mutexes(data, philosopher_head);
		free_memory(data, philosopher_head);
		free(data);
		return (NULL);
	}
	return (philosopher_head);
}

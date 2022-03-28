/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfuhl <jpfuhl@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:18:24 by jpfuhl            #+#    #+#             */
/*   Updated: 2022/03/28 19:18:41 by jpfuhl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_memory(t_data *data, t_philo *philosopher_head)
{
	int		i;
	t_philo	*next;
	t_philo	*current;

	i = 0;
	current = philosopher_head;
	while (i < data->number_of_philos)
	{
		next = current->next;
		free(current);
		current = next;
		if (!current)
			break ;
		i++;
	}
}

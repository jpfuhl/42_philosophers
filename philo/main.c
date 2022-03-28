/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfuhl <jpfuhl@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:05:43 by jpfuhl            #+#    #+#             */
/*   Updated: 2022/03/28 19:43:04 by jpfuhl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_format_message(void)
{
	printf("Please use this format: a b c d (e)\n");
	printf("a: number_of_philosophers\n");
	printf("b: time_to_die (in milliseconds)\n");
	printf("c: time_to_eat (in milliseconds)\n");
	printf("d: time_to_sleep (in milliseconds)\n");
	printf("e: number_of_times_each_philosopher_must_eat (optional)\n");
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*head;

	if (argc < 5 || 6 < argc)
	{
		print_format_message();
		return (-1);
	}
	if (check_input(argc, argv))
		return (-2);
	data = initialize_data(argc, argv);
	if (!data)
		return (-1);
	head = initialize_philosophers(data);
	if (!head)
		return (-3);
	handle_threads(data, head);
	if (data->number_of_meals != -1 && data->someone_died == FALSE)
		printf("Philosophers have eaten %d times.\n", data->number_of_meals);
	destroy_mutexes(data, head);
	free_memory(data, head);
	free(data);
	return (0);
}

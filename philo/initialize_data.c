/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfuhl <jpfuhl@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:08:46 by jpfuhl            #+#    #+#             */
/*   Updated: 2022/03/28 19:17:24 by jpfuhl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_skip_whitespace(const char *str)
{
	int	i;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == '+') && (str[i + 1] != '-'))
		i++;
	return (i);
}

long	ft_atol(const char *str)
{
	long	number;
	int		i;
	int		sign;

	number = 0;
	i = ft_skip_whitespace(str);
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	return (number * sign);
}

void	parse_input(t_data *data, int argc, char **argv)
{
	data->number_of_philos = ft_atol(argv[1]);
	if (argc == 6)
		data->number_of_meals = ft_atol(argv[5]);
	else
		data->number_of_meals = -1;
	pthread_mutex_init(&data->start, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
	data->time.start_time = 0;
	data->time.start_set = FALSE;
	data->time.dying = ft_atol(argv[2]);
	data->time.eating = ft_atol(argv[3]);
	data->time.sleeping = ft_atol(argv[4]);
	data->someone_died = FALSE;
}

t_data	*initialize_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	parse_input(data, argc, argv);
	return (data);
}

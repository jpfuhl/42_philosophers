/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfuhl <jpfuhl@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:51:33 by jpfuhl            #+#    #+#             */
/*   Updated: 2022/03/28 19:08:42 by jpfuhl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_if_digit(int c)
{
	if (48 <= c && c <= 57)
		return (1);
	return (0);
}

void	check_argument(char *arg, int *error)
{
	int	j;

	if (arg[0] == '\0')
	{
		*error = 1;
		return ;
	}
	j = 0;
	while (arg[j] != '\0')
	{
		if (check_if_digit(arg[j]) == 0)
			*error = 1;
		if (*error == 1)
			return ;
		j++;
	}
}

int	check_input(int argc, char **argv)
{
	int	error;
	int	i;

	error = 0;
	i = 1;
	while (i < argc)
	{
		check_argument(argv[i], &error);
		if (error == 1)
			break ;
		i++;
	}
	if (ft_atol(argv[1]) <= 0)
	{
		printf("ERROR: There must be at least 1 Philosopher.\n");
		return (1);
	}
	if (error == 1)
	{
		printf("ERROR: Please use only positive integers.\n");
		return (2);
	}
	return (0);
}

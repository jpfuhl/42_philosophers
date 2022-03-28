/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfuhl <jpfuhl@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:58:55 by jpfuhl            #+#    #+#             */
/*   Updated: 2022/03/28 19:20:00 by jpfuhl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

# define FALSE 0
# define TRUE 1

enum e_state
{
	DEFAULT,
	HAS_ONE_FORK,
	HAS_TWO_FORKS,
	EATING,
	SLEEPING,
	THINKING,
	FINISHED
};

typedef struct s_time
{
	long	start_time;
	bool	start_set;
	long	dying;
	long	eating;
	long	sleeping;
}	t_time;

typedef struct s_program_data
{
	bool			someone_died;
	int				number_of_philos;
	int				number_of_meals;
	pthread_mutex_t	start;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	t_time			time;
}	t_data;

typedef struct s_philosopher_node
{
	int							i;
	int							id;
	int							state;
	int							times_eaten;
	long						last_meal;
	pthread_mutex_t				fork;
	bool						fork_available;
	t_data						*data;
	pthread_t					thread;
	struct s_philosopher_node	*next;
}	t_philo;

/* PARSING */
/* ************************************************************************** */
/* check_input.c */
int		check_input(int argc, char **argv);
void	check_argument(char *arg, int *error);
int		check_if_digit(int c);

/* initialize_data.c */
t_data	*initialize_data(int argc, char **argv);
void	parse_input(t_data *data, int argc, char **argv);
long	ft_atol(const char *str);
int		ft_skip_whitespace(const char *str);

/* initialize_philosophers.c */
t_philo	*initialize_philosophers(t_data *data);
int		create_philo_list(t_philo *philosopher_head, t_data *data);
void	fill_with_data(t_philo *philosopher, t_data *data, int pos);
/* ************************************************************************** */

/* HANDLE THREADS */
/* ************************************************************************** */
/* handle_threads.c */
void	handle_threads(t_data *data, t_philo *head);
void	create_philo_threads(t_data *data, t_philo *head);
void	join_philo_threads(t_data *data, t_philo *head);

/* death.c */
void	*watch_philo_threads(void *arg);
bool	check_death(t_philo *philo);
void	kill_philo(t_philo *philo);
void	drop_all_forks(t_philo *philo);
/* ************************************************************************** */

/* PHILO MAIN */
/* ************************************************************************** */
/* philo_main.c */
void	*philo_launch(void *arg);
void	philo_main(t_philo *philo);
void	philo_decision(t_philo *philo);

/* philo_action.c */
void	start_eating(t_philo *philo);
void	start_sleeping(t_philo *philo);
void	start_thinking(t_philo *philo);

/* philo_forks.c */
void	take_own_fork(t_philo *philo);
void	take_next_fork(t_philo *philo);
void	drop_forks(t_philo *philo);
/* ************************************************************************** */

/* HELPER */
/* ************************************************************************** */
/* destroy_mutexes.c */
void	destroy_mutexes(t_data *data, t_philo *head);

/* free_memory.c */
void	free_memory(t_data *data, t_philo *philosopher_head);

/* time.c */
long	get_start_time(void);
long	get_current_time(t_philo *philo);
long	get_limit(t_philo *philo);
void	ft_sleep(t_philo *philo, long limit);
/* ************************************************************************** */

#endif
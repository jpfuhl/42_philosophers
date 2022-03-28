NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = main.c \
		check_input.c \
		death.c \
		destroy_mutexes.c \
		free_memory.c \
		handle_threads.c \
		initialize_data.c \
		initialize_philosophers.c \
		philo_action.c \
		philo_forks.c \
		philo_main.c \
		time.c \

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = philo.h
CFILES = philo.c \
		 parsing/ft_atoi.c \
		 parsing/philo_pars.c \
		 utils.c \
		 check_full_death.c
MOBJS = ${CFILES:.c=.o}

all: $(NAME)
$(NAME): $(MOBJS) $(INC)
	$(CC) $(FLAGS) $(FRAME) $(MOBJS) -o $(NAME)
%.o:%.c $(INC)
	cc $(CFLAGS) -c $< -o $@
clean :
	 rm -rf $(MOBJS)
fclean : clean
	 rm -rf $(NAME)
re : fclean all
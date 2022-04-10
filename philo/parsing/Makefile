NAME = philosophers
CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = philosophers.h
CFILES = philosophers.c \
		 parsing/ft_atoi.c \
		 parsing/philo_pars.c
MOBJS = ${CFILES:.c=.o}

all: $(NAME)
$(NAME): $(MOBJS) $(INC)
	$(CC) $(FLAGS) $(FRAME) $(MOBJS) -o $(NAME)
%.o:%.c $(INC)
	cc $(CFLAGS) -c $< -o $@
clean :
	 rm -rf $(MOBJS)
	 rm -rf $(BOBJS)
fclean : clean
	 rm -rf $(NAME)
re : fclean all
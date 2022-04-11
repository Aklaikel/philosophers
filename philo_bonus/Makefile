BNAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
BINC = philo_bonus.h
BFILES = philo_bonus.c \
		 parsing_bonus/ft_atoi.c \
		 parsing_bonus/philo_pars.c \
		 utils.c \
		 utils2.c
BOBJS = ${BFILES:.c=.o}

all: $(BNAME)
$(BNAME): $(BOBJS) $(BINC)
	$(CC) $(FLAGS) $(FRAME) $(BOBJS) -o $(BNAME)
%.o:%.c $(INC)
	cc $(CFLAGS) -c $< -o $@
clean :
	 rm -rf $(BOBJS)
fclean : clean
	 rm -rf $(BNAME)
re : fclean all
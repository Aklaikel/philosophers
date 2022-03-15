NAME = philosophers
CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = philosophers.h
CFILES = philosophers.c \
		 parsing/ft_atoi.c \
		 parsing/philo_pars.c \

# BFILES_x = 
	
# BFILES = $(addprefix bonus/, $(BFILES_x))

MOBJS = ${CFILES:.c=.o}
BOBJS = ${BFILES:.c=.o}

all: $(NAME)

$(NAME): $(MOBJS) $(INC)
	@$(CC) $(FLAGS) $(FRAME) $(MOBJS) -o $(NAME)

#bonus : $(BOBJS)
#	@$(CC) $(FLAGS) $(FRAME) $(BOBJS) -o $(BONUS_NAME)

%.o:%.c $(INC)
	@cc $(CFLAGS) -c $< -o $@
clean :
	@ rm -rf $(MOBJS)
	@ rm -rf $(BOBJS)
fclean : clean
	@ rm -rf $(NAME) $(BONUS_NAME)
re : fclean all
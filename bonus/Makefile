NAME = philosophers_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = philosophers_bonus.h
CFILES = philosophers_bonus.c \
		 parsing_bonus/ft_atoi.c \
		 parsing_bonus/philo_pars.c \

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
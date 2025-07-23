NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror 

SRC = main.c pars_arguments.c utils.c init.c simulation.c monitor.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	rm -f $(OBJ)

fclean : clean 
	rm -f $(NAME)

re : fclean all 

.SECONDARY:

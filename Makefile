CC = cc
CFALGS = -Wall -Wextra -Werror
SRCS = src/philosophers.c src/ft_atoi.c
OBJS = $(SRCS:.c=.o)
NAME = philo
all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFALGS) $(OBJS) -o $(NAME)
%.o: %.c
	$(CC) $(CFALGS) -c $< -o $@
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
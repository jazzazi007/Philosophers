CC = cc
CFALGS = -Wall -Wextra -Werror -fsanitize=thread
SRCS = src/philosophers.c src/ft_atoi.c src/init.c src/log.c src/get_time.c src/utils.c
OBJS = $(SRCS:.c=.o)
NAME = philo
all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFALGS) $(OBJS) -o $(NAME) -lpthread
%.o: %.c
	$(CC) $(CFALGS) -c $< -o $@
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
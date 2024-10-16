NAME = philo

SRC_DIR = .
SRC_FIL = mutex.c thread.c watcher.c time.c fork.c philo.c create_session.c simulation.c validation.c status.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FIL))

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc -g -Wall -Werror -Wextra $(OBJS) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	cc -g -Wall -Werror -Wextra -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


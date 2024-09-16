NAME = philo

SRC_DIR = src
SRC_FIL = math.c time.c fork.c hunger.c philo.c session.c simulation.c validation.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FIL))

OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(SRC_DIR), $(OBJS))

all: $(OBJS)
	cc -g -Wall -Werror -Wextra $(OBJS) -o $(NAME)

$(OBJS):
	cc -g -Wall -Werror -Wextra $(SRC) -c $< -o $@

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re $(OBJS)

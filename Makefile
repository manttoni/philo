SRC_DIR = src
SRC_FIL = fork.c hunger.c philo.c session.c simulation.c utils.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FIL))
all:
	cc -g -Wall -Werror -Wextra $(SRC) -o philo

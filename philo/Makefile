NAME = philo

CX = cc

CXFLAGS = -Wall -Werror -Wextra -g3

SRCS = main.c \
	utils.c \
	thread.c \
	init.c \
	philo.c \
	actions.c \
	ft_atoi.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
	$(CX) $(CXFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CX) $(CXFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re norm
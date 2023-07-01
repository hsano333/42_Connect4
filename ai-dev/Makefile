NAME = a.out
CC = cc
CFLAGS = -Wall -Wextra -fsanitize=address -g
SRCS	=	main.c \
			ai.c \
			utils.c \

OBJS	=	${SRCS:%.c=%.o}

all: ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${OBJS}

clean: 
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all
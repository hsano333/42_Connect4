NAME = a.out
CC = cc
CFLAGS = -Wall -Wextra 
SRCS	=	main.c \
			ai2.c \
			utils.c \
			set_board.c \

OBJS	=	${SRCS:%.c=%.o}

all: ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAGS} ${OBJS}

clean: 
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all
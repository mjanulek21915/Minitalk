CC = gcc

NAMES = server client

FLAGS = -Werror -Wextra -Wall

SRCS_S = 	server.c \
			lib.c

SRCS_C = 	client.c \
			lib.c

OBJS_S = $(SRCS_S:.c=.o)

OBJS_C = $(SRCS_C:.c=.o)


.PHONY : server client clean fclean all re

all : $(NAMES)

%.o : %.c
	$(CC) -c -o $@ $<

client : ${OBJS_C}
	$(CC) ${OBJS_C} -o client

server : ${OBJS_S}
	$(CC) ${OBJS_S} -o server


clean:
	rm -f $(OBJS_C)
	rm -f $(OBJS_S)
	
fclean: clean
	rm -f $(NAMES)

re: fclean all
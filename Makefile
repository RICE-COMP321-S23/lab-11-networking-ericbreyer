COURSE = /clear/www/htdocs/comp321
CC = cc
CFLAGS = -std=gnu11 -Wall -Wextra -Werror -g -I${COURSE}/include
LDFLAGS = -lpthread -lnsl -lrt

PROGS = echoclient echoserver

all: ${PROGS}

echoclient: echoclient.o csapp.o
	${CC} ${CFLAGS} -o echoclient echoclient.o csapp.o ${LDFLAGS}

echoserver: echoserver.o echo.o csapp.o
	${CC} ${CFLAGS} -o echoserver echoserver.o echo.o csapp.o ${LDFLAGS}

csapp.o: ${COURSE}/src/csapp.c ${COURSE}/include/csapp.h
	${CC} ${CFLAGS} -c ${COURSE}/src/csapp.c -o csapp.o

clean:
	${RM} *.o ${PROGS} core.[1-9]*

.PHONY: clean

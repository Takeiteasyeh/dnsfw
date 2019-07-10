OBJS	= src/dnsfw.o src/config.o
SOURCE	= src/dnsfw.c src/config.c
HEADER	= includes/dnsfw.h includes/config.h includes/hosts.h
OUT	= dnsfw
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -lpthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

src/dnsfw.o: src/dnsfw.c
	$(CC) $(FLAGS) src/dnsfw.c -o src/dnsfw.o

src/config.o: src/config.c
	$(CC) $(FLAGS) src/config.c -o src/config.o


clean:
	rm -f $(OBJS) $(OUT)

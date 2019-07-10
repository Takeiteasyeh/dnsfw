OBJS	= src/dnsfw.o src/config.o src/hosts.o src/version.o
SOURCE	= src/dnsfw.c src/config.c src/hosts.c src/version.c
HEADER	= includes/dnsfw.h includes/config.h includes/hosts.h includes/version.h
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

src/hosts.o: src/hosts.c
	$(CC) $(FLAGS) src/hosts.c -o src/hosts.o

src/version.o: src/version.c
	$(CC) $(FLAGS) src/version.c -o src/version.o

clean:
	rm -f $(OBJS) $(OUT)

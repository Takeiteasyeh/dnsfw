OBJS	= src/dnsfw.o src/iptables.o src/config.o src/hosts.o src/version.o src/debug.o
SOURCE	= src/dnsfw.c src/iptables.c src/config.c src/hosts.c src/version.c src/debug.c
HEADER	= includes/dnsfw.h include/iptables.h includes/config.h includes/hosts.h includes/version.h includes/debug.h
OUT	= dnsfw
CC	 = gcc
FLAGS	 = -std=gnu99 -g -c -Wall
LFLAGS	 = -lpthread
IDIR = includes
CFLAGS = -I$(IDIR)

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) $(CFLAGS)
	@echo Please modify dnsfw.conf before running:
	@echo make, make install, make service

src/iptables.o: src/iptables.c
	$(CC) $(FLAGS) src/iptables.c -o src/iptables.o $(CFLAGS)

src/config.o: src/config.c
	$(CC) $(FLAGS) src/config.c -o src/config.o $(CFLAGS)

src/hosts.o: src/hosts.c
	$(CC) $(FLAGS) src/hosts.c -o src/hosts.o $(CFLAGS)

src/version.o: src/version.c
	$(CC) $(FLAGS) src/version.c -o src/version.o $(CFLAGS)

src/dnsfw.o: src/dnsfw.c
	$(CC) $(FLAGS) src/dnsfw.c -o src/dnsfw.o $(CFLAGS)

src/debug.o: src/debug.c
	$(CC) $(FLAGS) src/debug.c -o src/debug.o $(CFLAGS)

clean:
	rm -f $(OBJS) $(OUT)

install:
	install -m 644 dnsfw /usr/sbin/
	install -m 644 dnsfw.conf /etc/
	@echo Please read INSTALL to continue.

service:
	install -m 644 dnsfw.service /etc/systemd/system/
	systemctl daemon-reload
	systemctl enable dnsfw.service
	systemctl start dnsfw.service
	@echo Done.

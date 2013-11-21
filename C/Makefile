.PHONY: all wschat clean

all: wschat

wschat: wschat.c
	gcc -I/usr/include/cdk -g -Wall wschat.c -lcdk -lncurses -lwebsockets\
		-L/lib -o WSChat

clean:
	rm -f *.o WSChat

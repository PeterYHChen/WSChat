.PHONY: all wschat clean

all: wschat

wschat: wschat.c
	gcc -I/usr/include/cdk -Wall wschat.c -lcdk -lncurses -L/lib -o WSChat

clean:
	rm -f *.o WSChat

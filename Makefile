DEBUG=
OBJS = main.c a4-util.o client.o header.h

all: main

main: $(OBJS)
	gcc $(DEBUG) -o main main.c client.o a4-util.o header.h

client.o: client.c
	gcc -Wall -c client.c

#client.o: client.c header.h a4-util.o
#	gcc $(DEBUG) -c client.c a4-util.o
#	gcc $(DEBUG) -o client client.c a4-util.o header.h main.o

clean:
	rm $(OBJS) main

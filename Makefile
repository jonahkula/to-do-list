COMPILE        = gcc -c -g -std=c99 -Wall
LINK           = gcc -g -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

Main : Main.o List.o
	$(LINK) $@ $^

Main.o : Main.c List.h
	$(COMPILE) Main.c

List.o : List.c List.h
	$(COMPILE) List.c

clean :
	$(REMOVE) Main *.o

memcheck : Main
	$(MEMCHECK) Main

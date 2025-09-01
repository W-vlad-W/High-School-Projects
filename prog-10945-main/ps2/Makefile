CC=gcc
CFLAGS=-std=c11 -Wall -Werror
LDLIBS=-lm
OUTPUT=game



all: $(OUTPUT)

$(OUTPUT): hof.o main.o k.o ui.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) hof.o main.o ui.o k.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

hof.o: hof.c hof.h
	$(CC) $(CFLAGS) -c hof.c -o hof.o

k.o: k.c k.h
	$(CC) $(CFLAGS) -c k.c -o k.o

ui.o: ui.c ui.h
	$(CC) $(CFLAGS) -c ui.c -o ui.o

clean:
	rm -rf $(OUTPUT) *.o


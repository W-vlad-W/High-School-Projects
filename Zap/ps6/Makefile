# variables
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wno-vla-parameter
LDLIBS=-lm -lcurses
OUTPUT=ship_war

# targets
all: $(OUTPUT)

$(OUTPUT): ship_war.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) ship_war.o $(LDLIBS) -o $(OUTPUT)


ship_war.o: ship_war.c ship_war.h
	$(CC) $(CFLAGS) -c ship_war.c $(LDLIBS) -o ship_war.o

# remove compiled files
clean: 
	rm -rf $(OUTPUT) *.o
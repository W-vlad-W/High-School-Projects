CC=gcc
CFLAGS=-std=c11 -Wall -Werror
LDLIBS=-lm
OUTPUT=ps1

all: $(OUTPUT)

$(OUTPUT): bmp.o main.o playfair.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) bmp.o main.o playfair.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

bmp.o: bmp.c bmp.h
	$(CC) $(CFLAGS) -c bmp.c -o bmp.o

playfair.o: playfair.c playfair.h
	$(CC) $(CFLAGS) -c playfair.c -o playfair.o

clean:
	rm -rf $(OUTPUT) *.o

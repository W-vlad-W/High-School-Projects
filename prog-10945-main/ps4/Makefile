CC = gcc
CFLAGS = -std=c11 -Werror -Wall
LDFLAGS = -lm

OBJ = bmp.o transformations.o main.o
TARGET = bmp

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

bmp.o: bmp.c bmp.h
	$(CC) $(CFLAGS) -c bmp.c

transformations.o: transformations.c transformations.h
	$(CC) $(CFLAGS) -c transformations.c

main.o: main.c bmp.h transformations.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(TARGET)

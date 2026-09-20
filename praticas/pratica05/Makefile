# Makefile modelo para Teoria dos Grafos

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -lm -Iestruturas
TARGET = main
SRC = *.c estruturas/*.c
OBJ = *.o

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) $(OBJ) main.exe

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

CC = gcc
CFLAGS = -Wall -Wextra -pedantic
LIBFLAGS = -lcurl
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXEC = ucs 

all: $(OBJ)
	$(CC) $(OBJ) $(LIBFLAGS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

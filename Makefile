CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = nanoshell
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC) nanoshell.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

re: clean all

.PHONY: all clean re

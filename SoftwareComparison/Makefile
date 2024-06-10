CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = main.c keyexpansion.c
OBJS = $(SRCS:.c=.o)
EXEC = program

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)
	./$(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

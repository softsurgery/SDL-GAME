CC = gcc
CFLAGS = $(shell sdl2-config --cflags) -Wall -Wextra
LIBS = $(shell sdl2-config --libs) -lSDL2_image
TARGET = app
SRCS = main.c menu.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean

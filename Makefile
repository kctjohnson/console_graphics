CC = g++
CFLAGS = -Wall -Wextra -ggdb
INCLUDES = -IHeaders -ISource
LIBS = -lncurses
TARGET = main
SRCS = main.cpp Source/vec.cpp

all:
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SRCS) $(LIBS)
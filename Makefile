CC = g++
CFLAGS = -Wall -Wextra -ggdb
INCLUDES = -IHeaders -ISource
LIBS = -lncursesw -pthread -lpng
TARGET = main
SRCS = main.cpp Source/vec.cpp Source/draw.cpp Source/boid.cpp

all:
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SRCS) $(LIBS)

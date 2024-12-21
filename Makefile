CC = g++
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = -Wextra -Wall
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = sfml_app

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(SFML_FLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(TARGET)

rebuild: clean all
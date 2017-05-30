#Makefile for compling the code

CC = g++

CPPFLAGS = -g -Wall

TARGET = raytracer

LIBS = -lm

SRCS := $(wildcard *.cpp)
INCS := $(wildcard *.h)
OBJS := $(SRCS:%.cpp=%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(LIBS) $(OBJS)
	
$(OBJS): %.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
	rm -f *.ppm

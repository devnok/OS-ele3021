# Compiler and Compile options.
CC = g++
CXXFLAGS = -g -Wall -std=c++11

# Macros specifying path for compile
SRCS := $(wildcard src/*.cc)
OBJS := $(SRCS:.cc=.o)
BIN = ./bin/
INC = ./include/
LIB = ./lib/ -lpthread

# Pre-Processor
CPPFLAGS += -I$(INC)

# Compile command.
TARGET = print_hello
$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -o $(BIN)$(TARGET) $(OBJS) -L$(LIB)

# Delete binary & object files.
clean:
	rm $(BIN)$(TARGET) $(OBJS)

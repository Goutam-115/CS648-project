# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -O3 -flto -march=native

# Source files
SRCS = algo1.cpp algo2.cpp algo3.cpp algo4.cpp data.cpp util.cpp

# Header files
HDRS = util.hpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Target executable
TARGET = algo1 algo2 algo3 algo4 data

# Default target
all: $(TARGET)

# Compile source files into object files
util.o: util.cpp util.hpp
	$(CC) $(CFLAGS) -c util.cpp -o util.o
algo1.o: algo1.cpp util.hpp
	$(CC) $(CFLAGS) -c algo1.cpp -o algo1.o
algo2.o: algo2.cpp util.hpp
	$(CC) $(CFLAGS) -c algo2.cpp -o algo2.o
algo3.o: algo3.cpp util.hpp
	$(CC) $(CFLAGS) -c algo3.cpp -o algo3.o
algo4.o: algo4.cpp util.hpp
	$(CC) $(CFLAGS) -c algo4.cpp -o algo4.o

algo1: algo1.o util.o
	$(CC) $(CFLAGS) algo1.o util.o -o algo1
algo2: algo2.o util.o
	$(CC) $(CFLAGS) algo2.o util.o -o algo2
algo3: algo3.o util.o
	$(CC) $(CFLAGS) algo3.o util.o -o algo3
algo4: algo4.o util.o
	$(CC) $(CFLAGS) algo4.o util.o -o algo4

data.o: data.cpp util.hpp
	$(CC) $(CFLAGS) -c data.cpp -o data.o
data: data.o util.o
	$(CC) $(CFLAGS) data.o util.o -o data

# Clean up object files and the target executable
clean:
	rm -f $(OBJS) $(TARGET)

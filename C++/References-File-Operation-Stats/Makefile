CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = main
SRC = main.cpp
OBJ = main.o

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

main.o: main.cpp stats.h
	$(CXX) $(CXXFLAGS) -c main.cpp

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)

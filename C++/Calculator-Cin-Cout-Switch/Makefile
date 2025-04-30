CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = main
SRC = main.cpp

build:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET)

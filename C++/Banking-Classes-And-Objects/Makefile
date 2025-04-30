CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = main
SRCS = main.cpp bank_account.cpp

build:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET)
